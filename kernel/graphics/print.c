#include "print.h"
#include "terminal.h"


void print(
    struct limine_framebuffer *fb,
    const char *text,
    uint32_t color
) {
    while (*text) {

        if (*text == '\n') {

            terminal_set_cursor_x(
                terminal_get_start_x()
            );

            terminal_set_cursor_y(
                terminal_get_cursor_y()
                + (8 * terminal_get_font_scale())
                + 2
            );

            text++;
            continue;
        }

        terminal_draw_char(
            fb,
            *text,
            terminal_get_cursor_x(),
            terminal_get_cursor_y(),
            color
        );

        terminal_set_cursor_x(
            terminal_get_cursor_x()
            + (8 * terminal_get_font_scale())
            + 1
        );

        text++;
    }
}
