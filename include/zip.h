#pragma once

#include <stddef.h>
#include <stdint.h>

// Flags
enum zip_general_flags {
	ZIP_FLAG_ENCRYPTED_FILE = 0, // Encrypted file
	ZIP_FLAG_COMPRESSION_OPTION1 = 2, // Compression option used
	ZIP_FLAG_COMPRESSION_OPTION2 = 4,
	ZIP_FLAG_DATA_DESCRIPTOR = 8, // Data descriptor present
	ZIP_FLAG_DEFLATE64 = 16, // Enhanced deflate used
	ZIP_FLAG_COMPRESSED_PATCHED = 32, // Compressed data was patched
	ZIP_FLAG_STRONG_ENCRYPTION = 64, // "Strong" (not really, according to
					 // Wikipedia) encryption
	ZIP_FLAG_LANGUAGE_ENCODING = 2048, // Language encoding
	ZIP_FLAG_MASK_HEADER_VALUES = 8192, // Mask header values
};

// Compression methods
enum zip_compression_method {
	ZIP_COMPRESSION_NONE = 0, // No compression
	ZIP_COMPRESSION_SHRUNK = 1, // Shrunken
	ZIP_COMRPESSION_REDUCE1 = 2, // Reduced with compression factor 1
	ZIP_COMPRESSION_REDUCE2 = 3, // Reduced with compression factor 2
	ZIP_COMPRESSION_REDUCE3 = 4, // Reduced with compression factor 3
	ZIP_COMPRESSION_REDUCE4 = 5, // Reduced with compression factor 4
	ZIP_COMPRESSION_IMPLODED = 6, // Imploded
	ZIP_COMPRESSION_DEFLATE = 8, // Compressed using zlib deflate
	ZIP_COMPRESSION_DEFLATE64 = 9, // Enhanced deflate
	ZIP_COMPRESSION_PK_DCL_IMPLODED = 10, // PKWare DCL imploded
	ZIP_COMPRESSION_BZIP2 = 12, // Compressed using BZIP2
	ZIP_COMPRESSION_LZMA = 14, // Compressed using LZMA
	ZIP_COMPRESSION_TERSE = 18, // Compressed using IBM TERSE
	ZIP_COMPRESSION_LZ77 = 19, // Compressed using IBM LZ77 z
	ZIP_COMPRESSION_PPMDII = 98, // Compressed using PPMd version I, rev. 1
};

// Local file header magic
#define ZIP_LOCAL_HEADER_MAGIC 0x04034b50

// Local file header
struct zip_local_file_hdr {
	uint32_t magic; // Must equal ZIP_LOCAL_HEADER_MAGIC
	uint16_t minimum_ver; // Minimum version needed to extract
	uint16_t flags; // Flags from zip_general_flags
	uint16_t method; // Compression method from zip_compression_method
	uint16_t mtime; // DOS-style modification time
	uint16_t mdate; // DOS-style modification date
	uint32_t crc; // CRC32 hash of uncompressed data
	uint32_t compressed_size; // Compressed data size
	uint32_t uncompressed_size; // Uncompressed data size
	uint16_t name_size; // File name size
	uint16_t extra_size; // Extra data size
};

// Data descriptor magic number
#define ZIP_DATA_DESCRIPTOR_MAGIC 0x08074b50

// Data descriptor (with magic number)
struct zip_data_descriptor_magic {
	uint32_t magic; // Magic number, optional (must equal
			// ZIP_DATA_DESCRIPTOR_MAGIC if present)
	uint32_t crc; // CRC32 of uncompressed data
	uint32_t compressed_size; // Compressed data size
	uint32_t uncompressed_size; // Uncompressed data size
};

// Data descriptor (without magic number)
struct zip_data_descriptor {
	uint32_t crc; // CRC32 of uncompressed data
	uint32_t compressed_size; // Compressed data size
	uint32_t uncompressed_size; // Uncompressed data size
};

// Central directory entry magic
#define ZIP_CENTRAL_DIRECTORY_ENTRY_MAGIC 0x02014b50

// Central directory entry
struct zip_central_directory_entry {
	uint32_t magic; // Magic number, must equal
			// ZIP_CENTRAL_DIRECTORY_ENTRY_MAGIC
	uint16_t version; // Version of the program that created this file
	uint16_t minimum_ver; // Minimum program version needed to extract
			      // this file
	uint16_t flags; // Flags from zip_general_flags
	uint16_t method; // Compression method from zip_compression_method
	uint16_t mtime; // DOS-style modification time
	uint16_t mdate; // DOS-style modification date
	uint32_t crc; // CRC32 of uncompressed data
	uint32_t compressed_size; // Compressed data size
	uint32_t uncompressed_size; // Uncompressed data size
	uint16_t name_size; // File name length
	uint16_t extra_size; // Extra data size
	uint16_t comment_size; // File comment size
	uint16_t disk; // Disk number where the file starts
	uint16_t internal_attrs; // Internal file attributes
	uint16_t external_attrs; // External file attributes
	uint16_t disk_to_local; // Offset from the start of the first disk the
				// file is on to its local header
};

// End of central directory magic
#define ZIP_END_OF_CENTRAL_DIRECTORY_MAGIC 0x06054b50

// End of central directory
struct zip_end_of_central_dir {
	uint32_t magic; // Magic number, must equal
			// ZIP_END_OF_CENTRAL_DIRECTORY_MAGIC
	uint16_t disk; // Number of this disk
	uint16_t disk_entries; // Number of central directory entries on this
			       // disk
	uint16_t total_entries; // Total number of central directory entries
	uint32_t directory_size; // Central directory size
	uint32_t directory_offset; // Offset of the central directory from the
				   // start of the archive
	uint16_t comment_size; // Archive comment length
};

