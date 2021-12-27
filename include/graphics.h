#pragma once

#include <stdint.h>

typedef uint32_t pixel_t;

union pixel_rgb {
	pixel_t pixel;
	pixel_t red:8;
	pixel_t green:8;
	pixel_t blue:8;
	pixel_t alpha:8;
};

union pixel_bgr {
	pixel_t pixel;
	pixel_t red:8;
	pixel_t green:8;
	pixel_t blue:8;
	pixel_t alpha:8;
};
