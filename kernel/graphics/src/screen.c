#include "graphics.h"

void fill_screen(struct kernel_boot_data *data, pixel_t pixel)
{
	size_t i;

	for (i = 0; i < data->framebuffer_size / sizeof(pixel_t); i++)
		data->framebuffer[i] = pixel_color(data, pixel);
}

void clear_screen(struct kernel_boot_data *data)
{
	size_t i;

	for (i = 0; i < data->framebuffer_size / sizeof(pixel_t); i++)
		data->framebuffer[i] = 0;
}
