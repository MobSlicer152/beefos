#ifndef _BEEFOS_STRING_H
#define _BEEFOS_STRING_H 1

#include <beefos/types.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int kmemcmp(const void *a, const void *b, size_t n);
void *kmemcpy(void *__restrict dst, const void *__restrict src, size_t n);
void *kmemmove(void * dst, const void * src, size_t n);
void *kmemset(void *buf, int val, size_t n);
size_t kstrlen(const char *str);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _BEEFOS_STRING_H */
