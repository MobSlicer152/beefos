#include <beefos/tty.h>

#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static const size_t VGA_AREA = VGA_WIDTH * VGA_HEIGHT;
static const u16 *VGA_MEM = (u16 *)0xC03FF000;

static size_t tty_row;
static size_t tty_col;
static u8 tty_color;
static u16 *tty_buf;

void tty_clear(void)
{
	tty_row = 0;
	tty_col = 0;
	tty_buf = VGA_MEM;

	size_t x;
	size_t y;

	for (y = 0; y < VGA_HEIGHT; y++) {
		for (x = 0; x < VGA_WIDTH; x++) {
			const size_t pos = y * VGA_WIDTH + x;
			tty_buf[pos] = vga_entry(' ', tty_color);
		}
	}
}

void tty_reset(void)
{
	tty_clear();

	tty_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
}

void tty_setcolor(u8 color)
{
	tty_color = color;
}

void tty_save(u16 *dst, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
		dst[i] = tty_buf[i];
}

void tty_scroll(size_t n)
{
	size_t i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < VGA_WIDTH; j++)
			tty_buf[j - 1] = tty_buf[j];
	}

	tty_row -= n;
}

void tty_putchar_at(uchar c, u16 color, size_t x, size_t y)
{
	const size_t pos = y * VGA_WIDTH + x;
	if (c > 0x20 && c < 0x7F) /* Ensure only visible ASCII characters are printed */
		tty_buf[pos] = vga_entry(c, color);

}

void tty_putchar(char c)
{
	unsigned char uc = c;
	tty_putchar_at(uc, tty_color, tty_col, tty_row);

	if (uc == '\b')
		tty_col--;

	if (++tty_col == VGA_WIDTH || uc == '\n') {
		tty_col = 0;
		tty_row++;

		if (++tty_row == VGA_HEIGHT) {
			tty_scroll(1);
		}
	}
}

size_t tty_nwrite(const char *data, size_t n)
{
	size_t i;
	size_t written = 0;

	for (i = 0; i < n; i++) {
		if (data[i] != -1) {
			tty_putchar(data[i]);
			written++;
		} else {
			return -1;
		}
	}

	return written;
}

size_t tty_write(const char *data)
{
	return tty_nwrite(data, kstrlen(data));
}
