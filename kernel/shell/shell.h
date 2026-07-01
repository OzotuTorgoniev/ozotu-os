#ifndef SHELL_H
#define SHELL_H

#include "../boot/limine.h"

typedef struct {
    struct limine_framebuffer *fb;
} Shell;

void shell_init(Shell *shell, struct limine_framebuffer *fb);
void shell_run(Shell *shell);

#endif
