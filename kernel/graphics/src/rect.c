#include "graphics.h"

void fill_rect(struct kernel_boot_data *data, struct point *a, struct point *b)
{
	size_t x;
	size_t y;

	for (x = a->x; x < b->x; x++) {
		for (y = a->y; y < b->y; y++)
			plot_pixel(data, &(struct point){a->pixel, x, y});
	}
}
