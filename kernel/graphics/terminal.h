#pragma once

#include <stdint.h>

#include "../boot/limine.h"

void terminal_backspace(struct limine_framebuffer *fb);
void terminal_clear(struct limine_framebuffer *fb);
void terminal_init(
    int start_x,
    int start_y
);

void terminal_set_font_scale(int scale);
int terminal_get_font_scale(void);

void terminal_draw_char(
    struct limine_framebuffer *fb,
    char c,
    int x,
    int y,
    uint32_t color
);

void terminal_draw_cursor(struct limine_framebuffer *fb);
void terminal_erase_cursor(struct limine_framebuffer *fb);

int terminal_get_cursor_x(void);
int terminal_get_cursor_y(void);

void terminal_set_cursor_x(int x);
void terminal_set_cursor_y(int y);

int terminal_get_start_x(void);
