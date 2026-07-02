#include "../../graphics/print.h"
#include "../../lib/string.h"
#include "../../lib/stddef.h"
#include "./cmd_sum.h"


void cmd_sum(Shell *shell, char *args) {
    char *arg1 = strtok(args, " ");
    char *arg2 = strtok(NULL, " ");

    if (arg1 == NULL || arg2 == NULL) {
        print(shell->fb, "Usage: sum <num1> <num2>\n", 0xFF0000);
        return;
    }

    int a = atoi(arg1);
    int b = atoi(arg2);

    int result = a + b;

    char buffer[16];
    itoa(result, buffer);

    print(shell->fb, buffer, 0x00FF00);
    print(shell->fb, "\n", 0xFFFFFF);
}
