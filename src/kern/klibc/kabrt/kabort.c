#include <beefos/kabrt.h>

__attribute__((__noreturn__))
void kabort(void)
{
	kprintf("oh sh*t a kernel panic: kabort() called\n");
	
	while (1) {}
	__builtin_unreachable();
}
