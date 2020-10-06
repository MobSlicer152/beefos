#ifndef _BEEFOS_MACRO_H
#define _BEEFOS_MACRO_H

#define BUF_EST_SIZE(b, type) (sizeof b / sizeof(type))

#define ARRAY_SIZE(a) (sizeof a/sizeof a[0])

#define CONCAT_INTS(hi, lo, type, target) (((target)(hi) << sizeof(type)) << 3 | (lo)) /*
										    * Shift hi by the size of type in bits (size in bytes left shifted by 3, in other words
										    * multiplied by 8), cast the result to target, and OR with lo (optimized by using shifts and ORing instead of addition/multiplication)
										    */

#endif /* _BEFFOS_MACRO_H */
