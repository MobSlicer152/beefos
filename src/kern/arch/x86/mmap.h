#ifndef _ARCH_X86_MMAP_H
#define _ARCH_X86_MMAP_H

#include <beefos/types.h>

struct mmap_ent {
	uint size;
	uint base_addr_lo, base_addr_hi;
	uint len_lo, len_hi;
	uint type;
};

#endif /* _ARCH_X86_MMAP_H */
