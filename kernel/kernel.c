#include "graphics/print.h"
#include "kernel.h"

#include "graphics/framebuffer.h"
#include "graphics/terminal.h"
#include "keyboard/keyboard.h"
#include "lib/string.h"

__attribute__((used, section(".limine_requests")))
static volatile LIMINE_BASE_REVISION(3);

volatile struct limine_framebuffer_request fb_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

// TESTES
void row(struct limine_framebuffer *fb, int length) {
    int i;

    print(fb, "\n", 0x00FF00);
    for (i = 0; i < length; i++) {
        print(fb, "=", 0x00FF00);
    }

    print(fb, "\n", 0x00FF00);
}

void sum_proc(struct limine_framebuffer *fb) {
    char xstr[16];
    char ystr[16];

    print(fb, "    sum>  x: ", 0xFFFFFF);
    keyboard_readline(fb, xstr, sizeof(xstr));

    print(fb, "\n    sum>  y: ", 0xFFFFFF);
    keyboard_readline(fb, ystr, sizeof(ystr));

    int x = atoi(xstr);
    int y = atoi(ystr);

    int sum = x + y;

    char result[16];
    itoa(sum, result);

    print(fb, "\n    sum>  r: ", 0xFFFFFF);
    print(fb, result, 0x00FF00);

    row(fb, 24);
}

void show_help(struct limine_framebuffer *fb) {
    print(fb, "\nAvailable cmds:\n", 0xFFFFFF);
    print(fb, "    'reboot' -- reboot the system.\n", 0xFFFFFF);
    print(fb, "    'clear'  -- clear terminal.\n", 0xFFFFFF);
    print(fb, "    'help'   -- show this help message.\n", 0xFFFFFF);
    print(fb, "    'sum'    -- sum x and y inputed values.\n", 0xFFFFFF);
}

// /TESTES

void kmain(void)
{
    if (!fb_request.response ||
        fb_request.response->framebuffer_count < 1)
    {
        for (;;)
            __asm__ volatile("hlt");
    }

    struct limine_framebuffer *fb =
        fb_request.response->framebuffers[0];

    fb_clear(fb, 0x000000);

    terminal_init(8, 8);
    keyboard_init();

    terminal_set_font_scale(4);
    print(fb, "WELCOME TO ", 0xFFFFFF);
    print(fb, "OZOTU OS!\n", 0x0000FF);

    terminal_set_font_scale(3);
    print(fb, "A free software developed with so many coffee and love!\n", 0xFFFFFF);
    row(fb, 64);
    print(fb, "\n", 0xFFFFFF);

    terminal_set_font_scale(2);

    while(1) {
        char cmd[64];

        print(fb, "guest@ozotu-os:~$  ", 0xFFFFFF);
        keyboard_readline(fb, cmd, sizeof(cmd));

        if (strcmp(cmd, "help") == 0) {
            show_help(fb);
        }
        else if (strcmp(cmd, "sum") == 0) {
            print(fb, "\n", 0xFFFFFF);
            sum_proc(fb);
        } else if (strcmp(cmd, "clear") == 0) {
            terminal_clear(fb);
        }

        print(fb, "\n", 0xFFFFFF);
    }

    for (;;)
        __asm__ volatile("hlt");
}
