#pragma once

#include <stdint.h>
#include "../boot/limine.h"

void fb_clear(
    struct limine_framebuffer *fb,
    uint32_t color
);
