#include "framebuffer.h"


void fb_clear(
    struct limine_framebuffer *fb,
    uint32_t color
) {
    uint32_t *pixels = fb->address;

    for (uint64_t y = 0; y < fb->height; y++) {
        for (uint64_t x = 0; x < fb->width; x++) {
            pixels[y * (fb->pitch / 4) + x] = color;
        }
    }
}
