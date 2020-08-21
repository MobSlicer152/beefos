#ifndef _BEEFOS_VGA_H
#define _BEEFOS_VGA_H

#ifdef __i386__
#include <arch/x86/vga.h>
#endif /* __i386__ */

#ifdef __x86_64__
#include <arch/x86_64/vga.h>
#endif

#endif /* _BEEFOS_VGA_H */
