#include <beefos/kstring.h>

int kmemcmp(const void *a, const void *b, size_t n)
{
	const uchar *aptr = (const uchar *)a;
	const uchar *bptr = (const uchar *)b;
	size_t i;

	for (i = 0; i < n; i++) {
		if (aptr[i] < bptr[i])
			return -1;
		else if (bptr[i] < aptr[i])
			return 1;
	}

	return 0;
}
