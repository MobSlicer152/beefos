#ifndef _BEEFOS_KABRT_H
#define _BEEFOS_KABRT_H

#include <beefos/asmbridge.h>
#include <beefos/vga.h>
#include <beefos/kprintf.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Abort the kernel. */
__attribute__((__noreturn__))
void kabort(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _BEEFOS_KABRT_H */
