#include "util.h"

void print_dos_mz_header(struct dos_mz_header *hdr)
{
	Print(L"DOS MZ header:\n    Magic: 0x%x\n    PE header offset: 0x%x\n",
	      hdr->signature, hdr->pe_header_rva);
}

void print_pe_header(struct pe_header *hdr)
{
	Print(L"PE header:\n    Magic: 0x%x %s\n    File header:\n        Architecture: 0x%x %s\n"
	      L"        Number of sections: %d\n        Timestamp: %d\n"
	      L"        Symbol table RVA: 0x%x\n        Number of symbols: %d\n"
	      L"        Optional header size: %d bytes\n        Characteristics: 0x%x",
	      hdr->magic,
	      hdr->magic == PE_HEADER_MAGIC ? L"(matches)" :
						    L"(does not match)",
	      hdr->file_hdr.architecture,
	      hdr->file_hdr.architecture == PE_ARCH_HOST ?
		      L"(matches host)" :
			    L"(does not match host)",
	      hdr->file_hdr.n_sections, hdr->file_hdr.timestamp,
	      hdr->file_hdr.symbol_table, hdr->file_hdr.n_symbols,
	      hdr->file_hdr.optional_header_size,
	      hdr->file_hdr.characteristics);

	// Print the optional header if it's present
	if (hdr->file_hdr.optional_header_size > 0) {
		Print(L"\n    Optional header (%d bytes):\n        Magic: 0x%x %s\n"
		      L"        Linker version: %d.%d\n        Text section size: %d bytes\n"
		      L"        Read-only data section size: %d bytes\n"
		      L"        Data section size: %d bytes\n        Entry point RVA: 0x%x\n"
		      L"        Text section RVA: 0x%x\n"
#ifdef __i386__
		      L"        Data section RVA: 0x%x\n        Preferred base address: 0x%x\n"
#else
		      L"        Preferred base address: 0x%lx\n"
#endif
		      L"        Section alignment: 0x%x\n        File alignment: 0x%x\n"
		      L"        Minimum Windows version: %d.%d\n        Image version: %d.%d\n"
		      L"        Minimum subsystem version: %d.%d\n        Image size: %d\n"
		      L"        Size of headers: %d bytes\n        Checksum: %d\n        Subsystem: %d\n"
		      L"        Characteristics: 0x%x\n"
#ifdef __i386__
		      L"        Maximum stack size: %d bytes\n        Initial stack size: %d\n"
		      L"        Maximum heap size: %d\n        Initial heap size: %d\n"
#else
		      L"        Maximum stack size: %ld bytes\n        Initial stack size: %ld\n"
		      L"        Maximum heap size: %ld\n        Initial heap size: %ld\n"
#endif
		      L"    Number of entries in the data directory: %d",
		      hdr->file_hdr.optional_header_size,
		      hdr->optional_hdr.magic,
		      hdr->optional_hdr.magic == PE_OPTIONAL_HEADER_MAGIC ?
			      L"(matches)" :
				    L" (does not match)",
		      hdr->optional_hdr.major_linker_version,
		      hdr->optional_hdr.minor_linker_version,
		      hdr->optional_hdr.text_size, hdr->optional_hdr.rdata_size,
		      hdr->optional_hdr.data_size, hdr->optional_hdr.entry,
		      hdr->optional_hdr.text_base,
#ifdef __i386__
		      hdr->optional_hdr.data_base,
#endif
		      hdr->optional_hdr.base, hdr->optional_hdr.section_align,
		      hdr->optional_hdr.file_align,
		      hdr->optional_hdr.major_system_version,
		      hdr->optional_hdr.minor_system_version,
		      hdr->optional_hdr.major_image_version,
		      hdr->optional_hdr.minor_image_version,
		      hdr->optional_hdr.major_subsys_version,
		      hdr->optional_hdr.minor_subsys_version,
		      hdr->optional_hdr.image_size,
		      hdr->optional_hdr.headers_size,
		      hdr->optional_hdr.checksum, hdr->optional_hdr.subsystem,
		      hdr->optional_hdr.characteristics,
		      hdr->optional_hdr.stack_max_size,
		      hdr->optional_hdr.stack_size,
		      hdr->optional_hdr.heap_max_size,
		      hdr->optional_hdr.heap_size,
		      hdr->optional_hdr.data_directory_count);
	}

	Print(L"\n");
}

void print_pe_section(struct pe_section_header *hdr)
{
	Print(L"");
}

void print_system_table(EFI_SYSTEM_TABLE *st)
{
	Print(L"UEFI spec revision: %d.%d\nFirmware vendor: %ls\n"
	      L"Firmware revision: %d.%d\n\n",
	      st->Hdr.Revision >> 16, st->Hdr.Revision & 0xFFFF,
	      st->FirmwareVendor, st->FirmwareRevision >> 16,
	      st->FirmwareRevision & 0xFFFF);
}

void *locate_protocol(EFI_GUID protocol_guid, EFI_HANDLE handle)
{
	EFI_STATUS status;
	EFI_HANDLE interface = NULL;

	// Try to locate the protocol
	status = BS->HandleProtocol(handle, &protocol_guid, &interface);
	if (EFI_ERROR(status)) {
		Print(L"Error: failed to locate protocol with GUID %g: %r\n",
		      protocol_guid, status);
		return NULL;
	}

	// Return
	Print(L"Found protocol with GUID %g at 0x0x%x\n", protocol_guid,
	      interface);
	return interface;
}
