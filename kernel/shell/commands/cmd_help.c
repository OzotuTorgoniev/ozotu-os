#include "../../graphics/print.h"
#include "./cmd_help.h"
#include "../ui.h"


void cmd_help(Shell *shell) {
    break_line(shell->fb);
    print(shell->fb, "    sum <num1> <num2> ----- Makes the num1 + num2 sum\n", 0xFFFFFF);
    print(shell->fb, "    clear ---------------- Clear the terminal\n", 0xFFFFFF);
    print(shell->fb, "    help ----------------- Show this help message\n", 0xFFFFFF);
    break_line(shell->fb);
}
