#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../limine/limine.h"

void keyboard_init(void);

char keyboard_getchar(void);

void keyboard_readline(
    struct limine_framebuffer *fb,
    char *buffer,
    int max
);

#endif
