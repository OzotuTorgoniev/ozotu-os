#include "./shell.h"


#ifndef COMMANDS_H
#define COMMANDS_H

typedef void (*CommandFunc)(Shell *shell, char *args);

typedef struct {
    const char *name;
    CommandFunc func;
} Command;

extern Command commands[];
extern const int command_count;

#endif
