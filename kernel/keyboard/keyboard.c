#include "../graphics/terminal.h"
#include "../graphics/print.h"
#include "keyboard.h"


static inline uint8_t inb(uint16_t port)
{
    uint8_t value;

    __asm__ volatile(
        "inb %1, %0"
        : "=a"(value)
        : "Nd"(port)
    );

    return value;
}

void keyboard_init(void)
{
}

static uint8_t keyboard_read_scancode(void)
{
    while (!(inb(0x64) & 1));

    return inb(0x60);
}

static const char keyboard_map[128] =
{
    0,
    27,
    '1','2','3','4','5','6','7','8','9','0','-','=',
    '\b',
    '\t',
    'q','w','e','r','t','y','u','i','o','p','[',']',
    '\n',
    0,
    'a','s','d','f','g','h','j','k','l',';','\'','`',
    0,
    '\\',
    'z','x','c','v','b','n','m',',','.','/',
    0,
    '*',
    0,
    ' ',
};

char keyboard_getchar(void)
{
    while (1)
    {
        uint8_t scancode = keyboard_read_scancode();

        if (scancode & 0x80)
            continue;

        if (scancode >= sizeof(keyboard_map))
            continue;

        char c = keyboard_map[scancode];

        if (c)
            return c;
    }
}

void keyboard_readline(
    struct limine_framebuffer *fb,
    char *buffer,
    int max
)
{
    int i = 0;

    buffer[0] = '\0';

    terminal_draw_cursor(fb);

    while (1)
    {
        char c = keyboard_getchar();

        terminal_erase_cursor(fb);

        if (c == '\n')
            break;

        if (c == '\b')
        {
            if (i > 0)
            {
                i--;

                buffer[i] = '\0';

                terminal_backspace(fb);
            }

            terminal_draw_cursor(fb);
            continue;
        }

        if (i >= max - 1)
        {
            terminal_draw_cursor(fb);
            continue;
        }

        buffer[i++] = c;
        buffer[i] = '\0';

        char s[2] = { c, '\0' };
        print(fb, s, 0xFFFFFF);

        terminal_draw_cursor(fb);
    }

    terminal_erase_cursor(fb);

    buffer[i] = '\0';
}
