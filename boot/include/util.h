#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <efi.h>
#include <efilib.h>

#include "executable.h"

// Print a DOS MZ header
extern void print_dos_mz_header(struct dos_mz_header *hdr);

// Print a PE header
extern void print_pe_header(struct pe_header *hdr);

// Print a PE section
extern void print_pe_section(struct pe_section_header *hdr);

// Print information from the System Table
extern void print_system_table(EFI_SYSTEM_TABLE *st);

// Convert a time_t value to an EFI_TIME structure
extern EFI_TIME epoch_to_efi_time(uint64_t t);

// Locate a protocol
extern void *locate_protocol(EFI_GUID protocol_guid, EFI_HANDLE handle);
