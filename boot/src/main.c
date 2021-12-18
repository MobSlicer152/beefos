#include <stddef.h>

#include <efi.h>
#include <efilib.h>

#include "executable.h"
#include "util.h"

EFI_STATUS EFIAPI efi_main(EFI_HANDLE image_handle,
			   EFI_SYSTEM_TABLE *system_table)
{
	EFI_STATUS status; // Status for various stuff
	EFI_LOADED_IMAGE_PROTOCOL *loaded_img; // Loaded image protocol
	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *boot_vol; // Handle to the boot volume
	EFI_FILE *root; // Handle to the root of the boot volume
	EFI_FILE *kernel; // Handle to the kernel file
	size_t size; // Variable for EFI file I/O to use
	struct dos_mz_header dos_hdr; // Kernel DOS header
	struct pe_header pe_hdr; // Kernel PE header
	struct pe_section_header *sections; // Kernel's sections

	// Set pointers to EFI services
	ST = system_table;
	BS = ST->BootServices;
	RT = ST->RuntimeServices;

	// Print the system table
	print_system_table(ST);

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

	return EFI_SUCCESS;
}
