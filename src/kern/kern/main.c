#include <beefos/kprintf.h>
#include <beefos/kstring.h>
#include <beefos/tty.h>
#include <beefos/vga.h>

void kernel_main(void)
{
	size_t i;

	tty_reset();

	tty_setcolor(15 | 0 << 4);

	kprintf("This is an intentionally long sentence that takes up a lot of space so that it wraps to the next line\n\n");

	for (i = 0; i < 80; i++) {
		tty_putchar_at(' ', vga_entry_color(i / 4, i / 4), i, i / 4 + 4);
	}
}
