#include "./graphics/terminal.h"
#include "./keyboard/keyboard.h"
#include "./shell/shell.h"
#include "kernel.h"


__attribute__((used, section(".limine_requests")))
static volatile LIMINE_BASE_REVISION(3);

volatile struct limine_framebuffer_request fb_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

void init_kernel() {
    Shell shell;

    struct limine_framebuffer *fb = fb_request.response->framebuffers[0];

    terminal_init(8, 8);
    keyboard_init();

    shell_init(&shell, fb);
    shell_run(&shell);
}

void kmain(void) {
    if (!fb_request.response || fb_request.response->framebuffer_count < 1) {
        for (;;)
            __asm__ volatile("hlt");
    }

    init_kernel();

    for (;;)
        __asm__ volatile("hlt");
}
