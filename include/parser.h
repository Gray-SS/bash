#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#define MAX_ARGS 256
#define DELIMITERS " \t\r\n\a"

typedef struct {
    char  **args;
    int     arg_count;

} command_t;

command_t   *parse_command(const char *input);
void         free_command(command_t *cmd);
int          is_valid_command(command_t *cmd);

#endif // PARSER_H