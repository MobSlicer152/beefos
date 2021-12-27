#include "boot.h"
#include "graphics.h"
#include "util.h"

pixel_t pixel_color(struct kernel_boot_data *data, pixel_t pixel)
{
	return data->framebuffer_bgr ? reverse_dword(pixel) : pixel;
}

void plot_pixel(struct kernel_boot_data *data, struct point *point)
{
	data->framebuffer[data->framebuffer_scanline_pixels * point->y + point->x] = pixel_color(data, point->pixel);
}
