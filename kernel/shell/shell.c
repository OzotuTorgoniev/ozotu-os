#include "../boot/limine.h"

// shell init
#include "../graphics/framebuffer.h"
#include "shell.h"

// shell run
#include "../graphics/terminal.h"
#include "../graphics/print.h"
#include "./ui.h"


void shell_init(Shell *shell, struct limine_framebuffer *fb) {
    shell->fb = fb;

    fb_clear(fb, 0x000000);
}

void print_welcome_message(Shell *shell) {
    terminal_set_font_scale(2);
    
    print(shell->fb, "WELCOME TO ", 0xFFFFFF);
    print(shell->fb, "OZOTU OS", 0x0000FF);
    print(shell->fb, "!\n", 0xFFFFFF);
    
    terminal_set_font_scale(1);
    print(shell->fb, "A free software OS developed with so MUCH coffe!\n", 0xFFFFFF);
    row(UI_ROW_LENGTH, 0x00FF00, shell->fb);
}

void shell_run(Shell *shell) {
    print_welcome_message(shell);
}
