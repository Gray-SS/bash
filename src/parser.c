#include "parser.h"
#include "shell.h"

command_t *parse_command(const char *input) {
    if (!input || input[0] == '\0') {
        return NULL;
    }

    command_t *cmd = malloc(sizeof(command_t));
    if (!cmd) {
        perror("malloc");
        return NULL;
    }

    cmd->arg_count = 0;
    cmd->args = (char **)malloc(sizeof(char*) * MAX_ARGS);

    if (!cmd->args) {
        perror("malloc");
        free(cmd);
        return NULL;
    }

    char *input_copy = strdup(input);
    if (!input_copy) {
        perror("strdup");
        free(cmd->args);
        free(cmd);
        return NULL;
    }

    int i = 0;
    char *token = strtok(input_copy, DELIMITERS);

    while (token && i < MAX_ARGS - 1) {
        cmd->args[i] = strdup(token);
        if (!cmd->args[i]) {
            perror("strdup");

            while (--i >= 0) {
                free(cmd->args[i]);
            }
            free(cmd->args);
            free(cmd);
            free(input_copy);
            return NULL;
        }

        i++;
        token = strtok(NULL, DELIMITERS);
    }

    cmd->arg_count = i;
    cmd->args[i] = NULL;

    free(input_copy);

    if (!is_valid_command(cmd)) {
        free_command(cmd);
        return NULL;
    }

    return cmd;
}

void free_command(command_t *cmd) {
    if (!cmd) return;

    free(cmd->args);
    free(cmd);
}

int is_valid_command(command_t *cmd) {
    if (cmd == NULL || cmd->arg_count == 0) {
        return 0;
    }

    return 1;
}