// Copyright (C) 2026 OZOTU OS Contributors

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.



#include <stdint.h>
#include <stddef.h>

#include "limine.h"

__attribute__((used, section(".limine_requests")))
static volatile LIMINE_BASE_REVISION(3);

static volatile struct limine_framebuffer_request fb_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

// A basic 8x8 bitmap font for the necessary letters: 'O', 'Z', 'T', 'U', 'S', ' '
// Each byte represents a line of 8 pixels (1 = pixel lit, 0 = pixel off)
static const uint8_t font8x8[6][8] = {
    {0x3C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C}, // 'O' (Index 0)
    {0x7E, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x7E, 0x00}, // 'Z' (Index 1)
    {0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18}, // 'T' (Index 2)
    {0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x7E, 0x00}, // 'U' (Index 3)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ' ' (Space - Index 4)
    {0x3C, 0x66, 0x06, 0x3C, 0x60, 0x66, 0x3C, 0x00}  // 'S' (Index 5)
};

// Maps the string "OZOTU OS" to the indices of our mini-source.
static const int string_indices[] = {0, 1, 0, 2, 3, 4, 0, 5};
#define STRING_LEN 8

void draw_char(struct limine_framebuffer *fb, int char_index, int start_x, int start_y, uint32_t color) {
    uint32_t *pixels = fb->address;
    
    for (int y = 0; y < 8; y++) {
        uint8_t row = font8x8[char_index][y];
        for (int x = 0; x < 8; x++) {
            // If the bit is active, it draws exactly 1 pixel (normal size 1:1).
            if ((row >> (7 - x)) & 1) {
                uint64_t pixel_x = start_x + x;
                uint64_t pixel_y = start_y + y;
                if (pixel_x < fb->width && pixel_y < fb->height) {
                    pixels[pixel_y * (fb->pitch / 4) + pixel_x] = color;
                }
            }
        }
    }
}

void kmain(void)
{
    if (!fb_request.response || fb_request.response->framebuffer_count < 1) {
        for (;;) __asm__ volatile("hlt");
    }

    struct limine_framebuffer *fb = fb_request.response->framebuffers[0];
    uint32_t *pixels = fb->address;

    // 1. Clear the screen (Black)
    for (uint64_t y = 0; y < fb->height; y++) {
        for (uint64_t x = 0; x < fb->width; x++) {
            pixels[y * (fb->pitch / 4) + x] = 0x000000;
        }
    }

    // 2. Draw the string "OZOTU OS" with normal size and spacing.
    int current_x = 8; // Subtle margin of the left edge
    int current_y = 8; // Subtle edge of the top border
    uint32_t text_color = 0xFFFFFF; // White

    for (int i = 0; i < STRING_LEN; i++) {
        draw_char(fb, string_indices[i], current_x, current_y, text_color);
        current_x += 9; // Moves the letter forward 8 pixels plus 1 pixel of space between them.
    }

    for (;;) {
        __asm__ volatile("hlt");
    }
}
