#pragma once

#include <stdint.h>

#include "boot.h"

// 32-bit pixel
typedef uint32_t pixel_t;

// RGB pixel (little endian)
union pixel_rgb {
	pixel_t pixel;
	pixel_t blue:8;
	pixel_t green:8;
	pixel_t red:8;
	pixel_t alpha:8;
};

// BGR pixel (little endian)
union pixel_bgr {
	pixel_t pixel;
	pixel_t red:8;
	pixel_t green:8;
	pixel_t blue:8;
	pixel_t alpha:8;
};

// A point on the screen
struct point {
	pixel_t pixel;
	size_t x;
	size_t y;
};

// Fill the screen with a color
extern void fill_screen(struct kernel_boot_data *data, pixel_t pixel);

// Clear the screen
extern void clear_screen(struct kernel_boot_data *data);

// Reverse a pixel if necessary
extern pixel_t pixel_color(struct kernel_boot_data *data, pixel_t pixel);

// Place a single pixel at point
extern void plot_pixel(struct kernel_boot_data *data, struct point *point);

// Fill a rectangle from point a to point b with a's color
extern void fill_rect(struct kernel_boot_data *data, struct point *a, struct point *b);
