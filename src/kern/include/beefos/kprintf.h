#ifndef _BEEFOS_KPRINTF_H
#define _BEEFOS_KPRINTF_H 1

#include <beefos/kstring.h>
#include <beefos/tty.h>

#include <limits.h>
#include <stdarg.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

ssize_t kprintf(const char *__restrict fmt, ...);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _BEEFOS_KPRINTF_H */
