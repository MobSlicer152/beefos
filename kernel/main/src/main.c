#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "boot.h"

void plot_pixel(struct kernel_boot_data *data, int x, int y, pixel_t pixel)
{
	data->framebuffer[data->framebuffer_scanline_pixels * y + x] = pixel;
}

void kernel_main(struct kernel_boot_data *data)
{
	size_t x;
	size_t y;

	for (x = 50; x < 100; x++) {
		for (y = 50; y < 100; y++)
			plot_pixel(data, x, y, 0x008800FF);
	}

	while (true)
		;
}
