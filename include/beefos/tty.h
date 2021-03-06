#ifndef _BEEFOS_TTY_H
#define _BEEFOS_TTY_H

#include <beefos/kstring.h>
#include <beefos/macro.h>
#include <beefos/types.h>

/* Resets buffer and cursor */
void tty_clear(void);

/* Resets buffer, cursor, and color */
void tty_reset(void);

/* Savesn bytes of the tty buffer into dst */
void tty_save(u16 *dst, size_t n);

/* Sets the background color of the terminal */
void tty_setcolor(u8 color);

/* Scrolls the buffer down n lines */
//void tty_scroll(size_t n);

/* Puts a character at the specified position in color */
void tty_putchar_at(uchar c, u16 color, size_t x, size_t y);

/* Puts a character at the cursor in the current color */
void tty_putchar(char c);

/* Writes n bytes of data in the current color */
size_t tty_nwrite(const char *data, size_t n);

/* Writes data in the current color */
size_t tty_write(const char *data);

#endif /* _BEEFOS_TTY_H */
