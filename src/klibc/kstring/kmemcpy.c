#include "beefos/kstring.h"

void *kmemcpy(void *restrict dst, const void *restrict src, size_t n)
{
	uchar *dstptr = (uchar *)dst;
	const uchar *srcptr = (const uchar *)src;
	size_t i;

	for (i = 0; i < n; i++)
		dstptr[i] = srcptr[i];

	return dst;
}
