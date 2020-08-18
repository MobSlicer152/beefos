#ifndef _BEEFOS_TTY_H
#define _BEFFOS_TTY_H

#include <stddef.h>

#include <beefos/kstring.h>
#include <beefos/types.h>

/* Reset buffer and cursor */
void tty_clear(void);

/* Reset buffer, cursor, and color */
void tty_reset(void);

/* Save n bytes of the tty buffer into dst */
void tty_save(u16 *dst, size_t n);

/* Set the background color of the terminal */
void tty_setcolor(u8 color);

/* Scroll the buffer down n lines */
void tty_scroll(size_t n);

/* Put a character at the specified position in color */
void tty_putchar_at(uchar c, u16 color, size_t x, size_t y);

/* Put a character at the cursor in the current color */
void tty_putchar(char c);

/* Write n bytes of data in the current color */
size_t tty_nwrite(const char *data, size_t n);

/* Write data in the current color */
size_t tty_write(const char *data);

#endif /* _BEEFOS_TTY_H */
