#include "../../graphics/terminal.h"
#include "./cmd_clear.h"


void cmd_clear(Shell *shell) {
    terminal_clear(shell->fb);
}
