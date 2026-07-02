#include "../boot/limine.h"

// shell init
#include "../graphics/framebuffer.h"
#include "shell.h"

// shell run
#include "../graphics/terminal.h"
#include "../keyboard/keyboard.h"
#include "../graphics/print.h"
#include "../lib/string.h"
#include "./commands.h"
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

#include <string.h>

void handle_command(Shell *shell, char cmd[]) {
    char *command = strtok(cmd, " ");

    if (command == NULL) {
        return;
    }

    char *args = strtok(NULL, "");

    if (args == NULL) {
        args = "";
    }

    for (int i = 0; i < command_count; i++) {
        if (strcmp(command, commands[i].name) == 0) {
            commands[i].func(shell, args);
            return;
        }
    }

    print(shell->fb, "Unknown command. Try 'help' to see available commands.\n", 0xFF0000);
}

void shell_run(Shell *shell) {
    print_welcome_message(shell);
    int running = 1;

    while (running) {
        char cmd[32];

        print(shell->fb, "ozotu-os@guest>>> ", 0xFFFFFF);
        keyboard_readline(shell->fb, cmd, 32);
        break_line(shell->fb);

        handle_command(shell, cmd);
    }

}
