#ifndef _BEEFOS_ASMBRIDGE_H
#define _BEEFOS_ASMBRIDGE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Panics the kernel. Defined in arch/<arch>/boot.S */
extern void _panic(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _BEEFOS_ASMBRIDGE_H */
