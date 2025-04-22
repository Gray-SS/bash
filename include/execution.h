#ifndef EXECUTION_H
#define EXECUTION_H

#include <string.h>

#include "parser.h"
#include "builtins.h"

int execute_command(command_t *cmd);
int execute_external_command(command_t *cmd);

#endif //EXECUTION_H