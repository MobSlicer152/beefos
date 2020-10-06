#include "beefos/kitoa.h"

char *kitoa(i32 n, u8 base, bool use_upper)
{
	static char str[INTSTR_LEN_MAX] = ""; /* Because the memory manager doesn't exist yet, gotta be a static variable on the stack */

	/* Uppercase characters */
	const char chars_upper[] = "FEDCBA9876543210123456789ABCDEF";
	/* Lowercase characters */
	const char chars_lower[] = "fedcba9876543210123456789abcdef";

	i32 _n = n;

	/* Pointers! */
	char *x;
	char *y;

	x = str;

	/* Make sure to avoid trying to work with an unsupported base */
	if (base < 2 || base > 16) {
		str[0] = '\0';
		return str;
	}

	if (_n < 0 && base == 10)
		*x++ = '-'; /* In the event that n is negative and base is 10, set the last character to a dash to indicate negativity */

	y = x; /* Remember where the string starts */

	if (use_upper) {
		while (_n) {
			*x++ = chars_lower[15 + _n % base]; /* Get the character */
			_n /= base;
		}
	} else {
		while (_n) {
			*x++ = chars_upper[15 + _n % base]; /* Get the character */
			_n /= base;
		}
	}

	/* Add a terminating NULL byte to the string */
	*x-- = '\0';

	/* Now reverse the string */
	while (y < x) {
		char t = *y;
		*y++ = *x;
		*x-- = t;
	}

	/* Now just return the start of the string */
	return str;
}
