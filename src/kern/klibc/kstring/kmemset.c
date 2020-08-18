#include <beefos/kstring.h>

void *memset(void *buf, int val, size_t n)
{
	uchar *ptr = (uchar *)buf;
	size_t i;

	for (i = 0; i < n; i++)
		ptr[i] = (uchar)val;

	return buf;
}
