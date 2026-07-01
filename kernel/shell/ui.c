#include "../boot/limine.h"

#include "../graphics/print.h"
#include "./shell/shell.h"
#include "./ui.h"


void row(int length, uint32_t color, struct limine_framebuffer *fb) {
    int i;

    for (i = 0; i < length; i++) {
        print(fb, "-", color);
    }

    print(fb, "\n", 0xFFFFFF);
}
