#include <stddef.h>

#include <efi.h>
#include <efilib.h>

#include "boot.h"
#include "executable.h"
#include "util.h"

EFI_STATUS EFIAPI efi_main(EFI_HANDLE image_handle,
			   EFI_SYSTEM_TABLE *system_table)
{
	EFI_STATUS status; // Status from EFI functions
	EFI_LOADED_IMAGE_PROTOCOL *loaded_img; // Loaded image protocol
	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *boot_vol; // Handle to the boot volume
	EFI_FILE *root; // Handle to the root of the boot volume
	EFI_FILE *kernel; // Handle to the kernel file
	size_t size; // Variable for EFI file I/O to use
	struct dos_mz_header dos_hdr; // Kernel DOS header
	struct pe_header pe_hdr; // Kernel PE header
	struct pe_section_header *sections; // Kernel's sections
	uint8_t *section_data; // Raw data of the current section
	size_t i; // Counter
	EFI_MEMORY_DESCRIPTOR *map = NULL; // Memory map
	size_t map_size = 0; // Size of the memory map
	size_t map_key; // Key for the current memory map (no clue what it's for other than ExitBootServices)
	size_t descriptor_size; // Size of the memory descriptor in memory
	uint32_t descriptor_version; // Version of the memory descriptor structure
	void *kernel_stack; // New stack for the kernel to use
	struct kernel_boot_data *kernel_data; // Data for the kernel

	// Set pointers to EFI services
	ST = system_table;
	BS = ST->BootServices;
	RT = ST->RuntimeServices;

	// Clear the screen
	ST->ConOut->ClearScreen(ST->ConOut);

	// Print the system table's information
	print_system_table(ST);

	// Disable the watchdog
	BS->SetWatchdogTimer(0, 0, 0, NULL);

	// Get the handle to the loaded image
	loaded_img = locate_protocol(LoadedImageProtocol, image_handle);
	if (!loaded_img) {
		Print(L"Error: failed to get the loaded image handle\n");
		return 1;
	}

	// Get the handle to the current device
	boot_vol =
		locate_protocol(FileSystemProtocol, loaded_img->DeviceHandle);
	if (!loaded_img) {
		Print(L"Error: failed to get the simple filesystem protocol for the boot volume\n");
		return 1;
	}

	// Open the boot volume
	Print(L"Opening boot volume...\n");
	status = boot_vol->OpenVolume(boot_vol, &root);
	if (status != EFI_SUCCESS) {
		Print(L"Error: failed to open the root of the boot volume: %r\n",
		      status);
		return status;
	}

	// Open the kernel
	Print(L"Opening kernel...\n");
	status = root->Open(root, &kernel, L"\\beefos\\kernel.sys",
			    EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY);
	if (status != EFI_SUCCESS) {
		Print(L"Error: failed to open the kernel: %r\n", status);
		return status;
	}

	Print(L"Parsing kernel...\n");

	// Parse the kernel's DOS header
	size = sizeof(struct dos_mz_header);
	kernel->Read(kernel, &size, &dos_hdr);
	print_dos_mz_header(&dos_hdr);
	if (dos_hdr.signature != DOS_MZ_SIGNATURE) {
		Print(L"Error: invalid DOS header in kernel, unable to locate PE header\n");
		return EFI_INVALID_PARAMETER;
	}

	// Parse the PE header
	kernel->SetPosition(kernel,
			    dos_hdr.pe_header_rva); // Seek to the PE header
	size = sizeof(struct pe_header) - PE_DATA_DIR_MAX_SIZE;
	kernel->Read(kernel, &size, &pe_hdr);
	print_pe_header(&pe_hdr);
	if (pe_hdr.magic != PE_HEADER_MAGIC ||
	    pe_hdr.file_hdr.architecture != PE_ARCH_HOST ||
	    pe_hdr.optional_hdr.magic != PE_OPTIONAL_HEADER_MAGIC) {
		Print(L"Error: invalid PE header in kernel\n");
		return EFI_INVALID_PARAMETER;
	}

	// Read the kernel's section headers
	kernel->GetPosition(kernel, &size);
	kernel->SetPosition(
		kernel,
		size + PE_DATA_DIR_SIZE(
			       pe_hdr.optional_hdr.data_directory_count));
	size = pe_hdr.file_hdr.n_sections * sizeof(struct pe_section_header);
	BS->AllocatePool(EfiLoaderData, size, &sections);
	kernel->Read(kernel, &size, sections);

	// Load the kernel's sections
	Print(L"Loading kernel sections...\n");
	kernel->SetPosition(kernel, pe_hdr.optional_hdr.headers_size); // The sections start here and can be read continuously without seeking
	for (i = 0; i < pe_hdr.file_hdr.n_sections; i++) {
		// Print the section
		print_pe_section(sections + i);

		// Allocate memory for the section
		size = sections[i].raw_size;
		section_data =
			(uint8_t *)(pe_hdr.optional_hdr.base + sections[i].rva);
		status = BS->AllocatePages(AllocateAddress,
					   sections[i].flags & PE_SECTION_EXEC ?
						   EfiLoaderCode :
							 EfiLoaderData,
					   EFI_SIZE_TO_PAGES(size),
					   &section_data);
		if (status != EFI_SUCCESS || !section_data) {
			Print(L"Error: failed to allocate %d page(s) (%ld bytes): %r\n",
			      EFI_SIZE_TO_PAGES(size), size, status);
			return status;
		}
		Print(L"Allocated %d page(s) (%ld bytes) of %s memory for section %a\n",
		      EFI_SIZE_TO_PAGES(size), size,
		      sections[i].flags & PE_SECTION_EXEC ? L"executable" :
								  L"writable",
		      sections[i].name);

		// Load the section's data
		size = sections[i].size;
		kernel->GetPosition(kernel, &i);
		Print(L"Loading section %a (%ld byte(s) from offset 0x%lX in the kernel) from 0x%lx to 0x%lx...\n",
		      sections[i].name, size, i, section_data,
		      section_data + EFI_SIZE_TO_PAGES(size) * EFI_PAGE_SIZE);
		status = kernel->Read(kernel, &size, section_data);
		if (status != EFI_SUCCESS) {
			Print(L"Error: failed to load section %a (%ld byte(s) from offset 0x%lX in the kernel) at 0x%lx: %r\n",
			      sections[i].name, size, i, section_data, status);
			return status;
		}
		Print(L"Loaded %ld bytes of section %a at 0x%lx\n", size,
		      sections[i].name, section_data);
	}

	// Allocate the kernel's stack
	Print(L"Successfully loaded kernel\n");
	size = pe_hdr.optional_hdr.stack_size;
	Print(L"Allocating %d bytes of stack space for the kernel...\n", size);
	status = BS->AllocatePages(AllocateAnyPages, EfiLoaderData,
				   EFI_SIZE_TO_PAGES(size), &kernel_stack);
	if (status != EFI_SUCCESS || !kernel_stack) {
		Print(L"Error: failed to allocate %d page(s) (%ld bytes) for the kernel stack:"
		      L" %r\n",
		      EFI_SIZE_TO_PAGES(size), size, status);
	}

	// Get the memory map
	Print(L"Getting memory map...\n");
	BS->GetMemoryMap(&map_size, map, &map_key, &descriptor_size,
			 &descriptor_version);
	map_size += 2 * descriptor_size;
	BS->AllocatePool(EfiLoaderData, map_size, &map);
	BS->GetMemoryMap(&map_size, map, &map_key, &descriptor_size,
			 &descriptor_version);
	Print(L"Memory map has %d %ld-byte version %ld descriptors totalling %ld bytes\n",
	      map_size / descriptor_size, descriptor_size, descriptor_version,
	      map_size);

	// Store things in the kernel's boot data, which goes at the bottom of the stack
	kernel_data = (void *)((uint8_t *)kernel_stack + size);
	kernel_data->efi_rt = ST->RuntimeServices;
	kernel_data->memory_map = map;
	kernel_data->memory_map_size = map_size;
	kernel_data->memory_map_ent_size = descriptor_size;

	// Exit boot services and jump into the kernel
	Print(L"Entering kernel in 5 seconds...\n");
	BS->Stall(5000000);
	Print(L"Jumping to kernel entry point at 0x%lX\n", (void *)(pe_hdr.optional_hdr.base + pe_hdr.optional_hdr.entry));
	BS->ExitBootServices(image_handle, map_key);
	enter_kernel(
		(void *)(pe_hdr.optional_hdr.base + pe_hdr.optional_hdr.entry),
		kernel_stack, size - sizeof(struct kernel_boot_data),
		kernel_data);

	return 0;
}
