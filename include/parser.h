#ifndef PARSER_H
#define PARSER_H

typedef struct {
    char   *name;
    char  **args;
    int     arg_count;

} command_t;

command_t *parse_command(const char *input);

#endif // PARSER_H