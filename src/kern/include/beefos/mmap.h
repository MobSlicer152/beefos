#ifndef _BEEFOS_MMAP_H
#define _BEEFOS_MMAP_H

#include <beefos/types.h>

/* Get the size of a block */
#define BLOCK_SIZE(hdr) (hdr.next - (&hdr - sizeof(hdr)))

struct mmap_ent {
	u32 size;
	u64 base_addr;
	u64 len;
	u32 type;
	struct block_hdr *header;
};

/* Roughly 36 bytes on x86 AFAIK */
struct block_hdr {
	uint len;
	bool used;
	bool was_used;
	bool is_end;
	void *block;
	struct block_hdr *next;
};

#endif /* _BEEFOS_MMAP_H_ */
