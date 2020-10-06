#ifndef _BEEFOS_KMEM_H
#define _BEEFOS_KMEM_H 1

#include <beefos/mmap.h>
#include <beefos/types.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void *kmalloc(size_t n);

void kfree(void *blk);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __BEEFOS_KMEM_H */
