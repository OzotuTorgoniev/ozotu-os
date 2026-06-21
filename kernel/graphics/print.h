#pragma once

#include <stdint.h>

#include "../boot/limine.h"

void print(
    struct limine_framebuffer *fb,
    const char *text,
    uint32_t color
);
