#include "beefos/kprintf.h"

ssize_t kprintf(const char *restrict fmt, ...)
{
	va_list args;
	size_t len;

	/* Variables used multiple times */
	char *str;
	i32 n;

	va_start(args, fmt);

	int written = 0;

	while (*fmt != '\0') {
		size_t max = INT_MAX - written;

		if (fmt[0] != '%' || fmt[1] == '%') {
			if (fmt[0] == '%')
				fmt++;

			size_t amount = 1;

			while (fmt[amount] && fmt[amount] != '%')
				amount++;

			if (max < amount) {
				// TODO: indicate the overflow that happened
				return -1;
			}

			if (!tty_nwrite(fmt, amount))
				return -1;

			fmt += amount;
			written += amount;

			continue;
		}

		const char *fmt_begun_at = fmt++;

		switch (*fmt) {
		case 'c':
			fmt++;
			
			char c = (char)va_arg(args, int);

			if (!max) {
				// TODO: indicate the overflow that happened
				return -1;
			}

			if (!tty_nwrite(&c, sizeof(c)))
				return -1;

			written++;
			
			break;
		case 's':
			fmt++;

			str = va_arg(args, const char *);
			len = kstrlen(str);
			if (max < len) {
				// TODO: indicate the overflow that happened
				return -1;
			}

			if (!tty_nwrite(str, len))
				return -1;

			written += len;

			break;
		case 'd':
			fmt++;

		        n = va_arg(args, int);
		        str = kitoa(n, 10, false);
		        len = kstrlen(str);
			if (max < len) {
				/* TODO: indicate the overflow that happened */
				return -1;
			}

			if (!tty_nwrite(str, len))
				return -1;

			written += len;

			break;
		case 'X':
			fmt++;

		        n = va_arg(args, uint);
		        str = kitoa(n, 16, true);
		        len = kstrlen(str);
			if (max < len) {
				/* TODO: indicate the overflow that happened */
				return -1;
			}

			if (!tty_nwrite(str, len))
				return -1;

			written += len;

			break;
		case 'x':
			fmt++;

		        n = va_arg(args, uint);
		        str = kitoa(n, 16, false);
		        len = kstrlen(str);
			if (max < len) {
				/* TODO: indicate the overflow that happened */
				return -1;
			}

			if (!tty_nwrite(str, len))
				return -1;

			written += len;

			break;
		case 'p':
			fmt++;

		        n = (u32)va_arg(args, void *);
		        str = kitoa(n, 16, true);
		        len = kstrlen(str);
			if (max < len) {
				/* TODO: indicate the overflow that happened */
				return -1;
			}

			if (!tty_nwrite("0x", len)) /* Probably not a great idea to have this separate, but whatever */
				return -1;
			if (!tty_nwrite(str, len))
				return -1;

			written += len;

			break;
		default:
			fmt = fmt_begun_at;

			len = kstrlen(fmt);
			if (max < len) {
				// TODO: indicate the overflow that happened
				return -1;
			}

			if (!tty_nwrite(fmt, len))
				return -1;

			written += len;
			fmt += len;

			break;
		}
	}

	va_end(args);
	return written;
}
