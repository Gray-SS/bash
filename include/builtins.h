#ifndef BUILTINS_H
#define BUILTINS_H

#include "execution.h"

typedef struct {
    const char *name;
    int (*func)(command_t *cmd);

} builtin_cmd_t;

int is_builtin(const char *cmd);
int execute_builtin_command(command_t *cmd);

int builtin_exit(command_t *cmd);
int builtin_pwd(command_t *cmd);
int builtin_cd(command_t *cmd);
int builtin_pwd(command_t *cmd);
int builtin_echo(command_t *cmd);

#endif //BUILTINS_H