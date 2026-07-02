#include "./commands.h"

// commands
#include "./commands/cmd_clear.h"
#include "./commands/cmd_help.h"
#include "./commands/cmd_sum.h"


Command commands[] = {
    { "clear", cmd_clear },
    { "help", cmd_help },
    { "sum", cmd_sum }
};

const int command_count = sizeof(commands) / sizeof(commands[0]);
