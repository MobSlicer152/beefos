#include "beefos/kstring.h"

void *memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	return kmemcpy(dst, src, n);
}
