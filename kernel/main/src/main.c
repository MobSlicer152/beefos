#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "boot.h"
#include "graphics.h"

void kernel_main(struct kernel_boot_data *data)
{
	// Clear the screen
	clear_screen(data);

	// Draw a square
	fill_rect(data,
		  &(struct point){ 0xFF008800, data->framebuffer_width / 2 - 50,
				   data->framebuffer_height / 2 - 50 },
		  &(struct point){ 0, data->framebuffer_width / 2 + 50,
				   data->framebuffer_height / 2 + 50 });

	while (true)
		;
}
