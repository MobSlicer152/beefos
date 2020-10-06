#include "beefos/kabrt.h"

__attribute__((__noreturn__))
void kabort(void)
{
	tty_setcolor(vga_entry_color(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK));
	kprintf("Oh sh*t a kernel panic! This is bad. Reason: kabort() called\n");
	
	while (1) {}
	__builtin_unreachable();
}
