#include "graphics/print.h"
#include "kernel.h"

#include "graphics/framebuffer.h"
#include "graphics/terminal.h"

__attribute__((used, section(".limine_requests")))
static volatile LIMINE_BASE_REVISION(3);

volatile struct limine_framebuffer_request fb_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

void kmain(void)
{
    if (
        !fb_request.response ||
        fb_request.response->framebuffer_count < 1
    ) {
        for (;;) {
            __asm__ volatile("hlt");
        }
    }

    struct limine_framebuffer *fb =
        fb_request.response->framebuffers[0];

    fb_clear(fb, 0x000000);
    terminal_init(8, 8);

    terminal_set_font_scale(2);
    print(fb,"WELCOME TO OZOTU OS! \n" ,0xFFFFFF);

    terminal_set_font_scale(1);
    print(fb,"A free software developed with so many coffee and love! \n" ,0xFFFFFF);

    for (;;) {
        __asm__ volatile("hlt");
    }
}
