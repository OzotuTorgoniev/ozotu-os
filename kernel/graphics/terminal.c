#include "../../font8x8/font8x8_basic.h"
#include "framebuffer.h"
#include "terminal.h"


static int cursor_x = 0;
static int cursor_y = 0;

static int start_x = 0;

static int font_scale = 1;

void terminal_init(
    int x,
    int y
) {
    start_x = x;

    cursor_x = x;
    cursor_y = y;
}

void terminal_set_font_scale(int scale)
{
    if (scale < 1) {
        scale = 1;
    }

    font_scale = scale;
}

int terminal_get_font_scale(void)
{
    return font_scale;
}

int terminal_get_cursor_x(void)
{
    return cursor_x;
}

int terminal_get_cursor_y(void)
{
    return cursor_y;
}

void terminal_set_cursor_x(int x)
{
    cursor_x = x;
}

void terminal_set_cursor_y(int y)
{
    cursor_y = y;
}

int terminal_get_start_x(void)
{
    return start_x;
}

void terminal_draw_char(
    struct limine_framebuffer *fb,
    char c,
    int start_x,
    int start_y,
    uint32_t color
) {
    const unsigned char *glyph =
        (unsigned char *)font8x8_basic[(unsigned char)c];

    uint32_t *pixels = fb->address;

    for (int y = 0; y < 8; y++) {

        uint8_t row = glyph[y];

        for (int x = 0; x < 8; x++) {

            if ((row >> x) & 1) {

                for (int sy = 0; sy < font_scale; sy++) {

                    for (int sx = 0; sx < font_scale; sx++) {

                        uint64_t pixel_x =
                            start_x +
                            (x * font_scale) +
                            sx;

                        uint64_t pixel_y =
                            start_y +
                            (y * font_scale) +
                            sy;

                        if (
                            pixel_x < fb->width &&
                            pixel_y < fb->height
                        ) {
                            pixels[
                                pixel_y * (fb->pitch / 4)
                                + pixel_x
                            ] = color;
                        }
                    }
                }
            }
        }
    }
}

void terminal_clear(struct limine_framebuffer *fb)
{
    fb_clear(fb, 0x000000);

    terminal_set_cursor_x(8);
    terminal_set_cursor_y(8);
}

void terminal_backspace(struct limine_framebuffer *fb)
{
    int width = (8 * terminal_get_font_scale()) + 1;

    if (cursor_x <= start_x)
        return;

    cursor_x -= width;

    uint32_t *pixels = fb->address;

    for (int y = 0; y < 8 * font_scale; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int px = cursor_x + x;
            int py = cursor_y + y;

            if (px >= 0 &&
                py >= 0 &&
                (uint64_t)px < fb->width &&
                (uint64_t)py < fb->height)
            {
                pixels[py * (fb->pitch / 4) + px] = 0x000000;
            }
        }
    }
}

void terminal_draw_cursor(struct limine_framebuffer *fb)
{
    uint32_t *pixels = fb->address;

    int x = cursor_x;
    int y = cursor_y + (8 * font_scale);

    for (int py = 0; py < 2; py++)
    {
        for (int px = 0; px < 8 * font_scale; px++)
        {
            pixels[(y + py) * (fb->pitch / 4) + (x + px)] = 0xFFFFFF;
        }
    }
}

void terminal_erase_cursor(struct limine_framebuffer *fb)
{
    uint32_t *pixels = fb->address;

    int x = cursor_x;
    int y = cursor_y + (8 * font_scale);

    for (int py = 0; py < 2; py++)
    {
        for (int px = 0; px < 8 * font_scale; px++)
        {
            pixels[(y + py) * (fb->pitch / 4) + (x + px)] = 0x000000;
        }
    }
}
