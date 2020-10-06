#include "beefos/kstring.h"

void *kmemmove(void *dst, const void *src, size_t n)
{
	uchar *dstptr = (uchar *)dst;
	const uchar *srcptr = (const uchar *)src;
	size_t i;

	if (dstptr < srcptr)
		for (i = 0; i < n; i++)
			dstptr[i] = srcptr[i];
	else
		for (i = n; i > 0; i--)
			dstptr[i - 1] = srcptr[i - 1];

	return dst;	
}
