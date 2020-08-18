#include <beefos/kprintf.h>
#include <beefos/kstring.h>
#include <beefos/tty.h>

void kernel_main(void)
{
	size_t i, j;
	
	tty_reset();
	for (i = 0; i < 24; i++) {
		tty_putchar_at(' ', 5 | 5 << 4, 0, i);
		
		for (j = 0; j < 80; j++)
			tty_putchar_at(' ', 5 | 5 << 4, j, i);
	}

	for (i = 0; i < 10000; i++) {
		if (i == 10000)
			tty_scroll(2);
	}
}
