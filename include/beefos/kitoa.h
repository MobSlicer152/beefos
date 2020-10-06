#ifndef _BEEFOS_ITOA_H
#define _BEEFOS_ITOA_H 1

#include <stdbool.h>

#include <beefos/kstring.h>
#include <beefos/macro.h>

#define INTSTR_LEN_MAX 20 /* No valid integer (because it's not like integer values can use the 128-/256-bit registers) is going to be longer than this for a while. */
#define UINTSTR_LEN_MAX 24 /* Same deal here */

/* Returns a buffer containing the digits of n in base base as characters */
char *kitoa(i32 n, u8 base, bool use_upper);

#endif /* !_BEEFOS_ITOA_H */
