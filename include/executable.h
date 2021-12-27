#pragma once

#include <stddef.h>
#include <stdint.h>

// DOS MZ signature
#define DOS_MZ_SIGNATURE 0x5A4D

// DOS MZ header. "Pages" refer to 512-byte blocks, "paragraphs" are 16 bytes
struct dos_mz_header {
	// Original header format
	uint16_t signature; // The characters MZ
	uint16_t extra; // Number of extra bytes in the last page
	uint16_t pages; // Number of pages needed for the image
	uint16_t n_relocs; // Number of relocation entries
	uint16_t code_offset; // Offset of the real-mode code of the executable
	uint16_t min_alloc; // Minimum number of paragraphs for the executable to function
	uint16_t ideal_alloc; // Ideal number of paragraphs for the executable
	uint16_t init_ss; // Initial relocatable stack segment descriptor value
	uint16_t init_sp; // Initial stack pointer value
	uint16_t checksum; // Must equal zero when added to all other words in the executable
	uint16_t init_ip; // Initial instruction pointer value
	uint16_t init_cs; // Initial relocatable code segment descriptor value
	uint16_t reloc_offset; // Offset to the relocation table
	uint16_t overlay; // Overlay value. Not used by PE executables.

	// PE support extension
	uint64_t reserved1; // Reserved for future use
	uint16_t oem_ident; // OEM identifier. Not used
	uint16_t oem_info; // OEM information. Not used
	uint8_t reserved2[16]; // Reserved bytes
	uint32_t pe_header_rva; // Relative virtual address of the PE header
};

// PE file machine architectures
#define PE_ARCH_UNKNOWN 0 // Unknown architecture
#define PE_ARCH_I386 0x14C // 32-bit x86 (not just the 80386)
#define PE_ARCH_AMD64 0x8664 // AMD's 64-bit extension to x86 (Athlon 64 and above)
#define PE_ARCH_ARM64 0xAA64 // ARMv8 and above, also known as aarch64
#ifdef __i386__
#define PE_ARCH_HOST PE_ARCH_I386
#elif defined __x86_64__
#define PE_ARCH_HOST PE_ARCH_AMD64
#elif defined __arm__
#define PE_ARCH_HOST PE_ARCH_ARM64
#endif

// PE file header. Contains basic information about the executable
struct pe_file_header {
	uint16_t architecture; // Image architecture (PE_ARCH_* constants)
	uint16_t n_sections; // Number of sections in the image
	uint32_t timestamp; // Timestamp of when the image was created. Often 0 or negative.
	uint32_t symbol_table; // RVA of the symbol table
	uint32_t n_symbols; // Number of symbol table entries
	uint16_t optional_header_size; // Size of the optional header
	uint16_t characteristics; // Characteristics of the executable
};

// PE data directory entries
enum pe_data_dir_entry {
	PE_DATA_DIR_EXPORT = 0, // Export table
	PE_DATA_DIR_IMPORT, // Import table
	PE_DATA_DIR_RESOURCE, // Resource table
	PE_DATA_DIR_EXCEPTION, // Exception table
	PE_DATA_DIR_CERTIFICATE, // Certificate table
	PE_DATA_DIR_RELOC, // Relocation table
	PE_DATA_DIR_DEBUG, // Debug info
	PE_DATA_DIR_ARCHITECTURE, // Architecure-specific information
	PE_DATA_DIR_GLOBAL_PTR, // Global pointer register value
	PE_DATA_DIR_TLS, // Thread local storage table
	PE_DATA_DIR_LOAD_CONFIG, // Load configuration table
	PE_DATA_DIR_BOUND_IMPORT, // Bound import table
	PE_DATA_DIR_IMPORT_ADDR, // Import address table
	PE_DATA_DIR_DELAY_IMPORT, // Delay import descriptor
	PE_DATA_DIR_CLR_HEADER, // .NET VM header
	PE_DATA_DIR_RESERVED, // Reserved data directory
	PE_DATA_DIR_MAX_ENTRIES // Maximum entries in the data directory
};

// PE data directory
struct pe_data_directory {
	uint32_t rva; // RVA of the data
	uint32_t size; // Size of the data
};

// PE data directory max size
#define PE_DATA_DIR_MAX_SIZE (PE_DATA_DIR_MAX_ENTRIES * sizeof(struct pe_data_directory))

// PE data directory size
#define PE_DATA_DIR_SIZE(entry_count) ((entry_count) * sizeof(struct pe_data_directory)) 

// PE optional header magic value
#ifdef __i386__
#define PE_OPTIONAL_HEADER_MAGIC 0x10B
#else
#define PE_OPTIONAL_HEADER_MAGIC 0x20B
#endif

// PE optional header. Contains many important values, and several Windows-specific fields.
struct pe_optional_header {
	uint16_t magic; // Must be 0x10B for 32-bit, 0x20B for 64-bit
	uint8_t major_linker_version; // Major linker version
	uint8_t minor_linker_version; // Minor linker version
	uint32_t text_size; // Size of the .text section
	uint32_t rdata_size; // Size of all read-only data sections
	uint32_t data_size; // Size of all uninitialized writable data section
	uint32_t entry; // RVA of the entry point
#ifdef __i386__ // x86 is the only 32-bit architecture supported
	uint32_t text_base; // RVA of the start of the .text section
	uint32_t data_base; // Rva of the start of the .data section
	uint32_t base; // Base address of the image
#else
	uint32_t text_base; // RVA of the start of the .text section
	uint64_t base; // Base address of the image
#endif
	uint32_t section_align; // Section alignment
	uint32_t file_align; // File alignment
	uint16_t major_system_version; // Major required operating system version
	uint16_t minor_system_version; // Minor required operating system version
	uint16_t major_image_version; // Major image version
	uint16_t minor_image_version; // Minor image version
	uint16_t major_subsys_version; // Major subsystem version
	uint16_t minor_subsys_version; // Minor subsystem version
	uint32_t reserved; // Reserved
	uint32_t image_size; // How much space the executable needs to function when loaded into memory
	uint32_t headers_size; // Size of some of the executable's headers. Check the docs for IMAGE_OPTIONAL_HEADER for more.
	uint32_t checksum; // Checksum of the executable. Should probably be implemented at some point.
	uint16_t subsystem; // Subsystem of the image
	uint16_t characteristics; // Flags for the image
#ifdef __i386__
	uint32_t stack_max_size; // Maximum stack size
	uint32_t stack_size; // Initial stack size
	uint32_t heap_max_size; // Maximum heap size
	uint32_t heap_size; // Initial heap size
#else
	uint64_t stack_max_size; // Maximum stack size
	uint64_t stack_size; // Initial stack size
	uint64_t heap_max_size; // Maximum heap size
	uint64_t heap_size; // Initial heap size
#endif
	uint32_t loader_flags; // Superseded by characteristics
	uint32_t data_directory_count; // Number of entries in data_directory
};

// PE header magic
#define PE_HEADER_MAGIC 0x4550

// Full PE header. In separate structs because the optional header can technically be empty.
struct pe_header {
	uint32_t magic; // Magic signature, must be 0x4550 in little endian
	struct pe_file_header file_hdr; // File header, always present
	struct pe_optional_header optional_hdr; // Optional header, present if file_hdr.optional_header_size is greater than 0
	struct pe_data_directory data_directory[PE_DATA_DIR_MAX_ENTRIES]; // The data directory
};

// PE section flags. Only these flags are checked when sections are parsed.
enum pe_section_flags {
	PE_SECTION_CODE = 0x20, // The section contains code
	PE_SECTION_INITIALIZED = 0x40, // The section contains initialized data
	PE_SECTION_UNINITIALIZED = 0x80, // The section contains uninitialized data
	PE_SECTION_MANY_RELOCS = 0x1000000, // The section contains more than UINT16_MAX relocation entries
	PE_SECTION_DISCARDABLE = 0x2000000, // The section can be discarded
	PE_SECTION_EXEC = 0x20000000, // The section is executable
	PE_SECTION_READ = 0x40000000, // The section is readable
	PE_SECTION_WRITE = 0x80000000, // The section is writable
};

// PE section header
struct pe_section_header {
	uint8_t name[8]; // Section name
	uint32_t size; // Size of the section when it's loaded
	uint32_t rva; // RVA of the section
	uint32_t raw_size; // Size of the raw data in the section
	uint32_t raw_data; // RVA of the raw data in the section
	uint32_t relocs; // RVA of the relocations in the section
	uint32_t line_numbers; // RVA of the line number information of the section
	uint16_t n_relocs; // Number of relocations in the section
	uint16_t n_line_numbers; // Number of line numbers stored in the section
	uint32_t flags; // Flags for the section
};
