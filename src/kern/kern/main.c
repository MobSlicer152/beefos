#include <beefos/kprintf.h>
#include <beefos/kstring.h>
#include <beefos/tty.h>

void kernel_main(void)
{
	tty_reset();
	
	tty_setcolor(3 | 0 << 4);

	tty_putchar_at(' ', 3 | 3 << 4, 39, 11);
	tty_putchar_at(' ', 3 | 3 << 4, 40, 11);
	tty_putchar_at(' ', 3 | 3 << 4, 41, 11);
	tty_putchar_at(' ', 3 | 3 << 4, 42, 11);
	tty_putchar_at(' ', 3 | 3 << 4, 39, 12);
	tty_putchar_at(' ', 3 | 3 << 4, 40, 12);
	tty_putchar_at(' ', 3 | 3 << 4, 41, 12);
	tty_putchar_at(' ', 3 | 3 << 4, 42, 12);
}
