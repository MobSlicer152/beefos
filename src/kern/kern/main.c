#include <beefos/kprintf.h>
#include <beefos/kstring.h>
#include <beefos/tty.h>

void kernel_main(void)
{
	size_t i;

	tty_reset();

	tty_setcolor(15 | 0 << 4);

	kprintf("This is a really basic OS that is crazy simple. This is an intentionally long sentence that takes up a lot of space\n\n");

	for (i = 0; i < 80; i++) {
		tty_putchar_at(' ', i / 4 + 1 | i / 4 + 1 << 4, i, i / 4 + 4);
	}
}
