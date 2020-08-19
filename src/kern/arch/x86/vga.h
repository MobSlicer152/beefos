#ifndef _ARCH_I386_VGA_H
#define _ARCH_I386_VGA_H

#include <beefos/types.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum vga_color {
	VGA_COLOR_BLACK,
	VGA_COLOR_BLUE,
	VGA_COLOR_GREEN,
	VGA_COLOR_CYAN,
	VGA_COLOR_RED,
	VGA_COLOR_MAGENTA,
	VGA_COLOR_ORANGE,
	VGA_COLOR_LIGHT_GREY,
	VGA_COLOR_DARK_GREY,
	VGA_COLOR_LIGHT_BLUE,
	VGA_COLOR_LIGHT_GREEN,
	VGA_COLOR_LIGHT_CYAN,
	VGA_COLOR_LIGHT_RED,
	VGA_COLOR_LIGHT_MAGENTA,
	VGA_COLOR_LIGHT_ORANGE,
	VGA_COLOR_WHITE
};

static inline u8 vga_entry_color(u8 fg, u8 bg)
{
	return fg | bg << 4;
}

static inline u16 vga_entry(u8 uc, u16 color)
{
	return (u16)uc | (u16)color << 8;
} 

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _ARCH_I386_VGA_H */
