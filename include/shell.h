#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>

#include "parser.h"
#include "execution.h"

#define MAX_ARGS 256
#define MAX_INPUT_SIZE 4096
#define MAX_PATH_LENGTH 1024
#define MAX_HOSTNAME_LENGTH 256
#define DELIMITERS " \t\r\n\a"

typedef struct {
    char   *username;
    char   *hostname;
    char    crnt_dir[MAX_PATH_LENGTH];

    int     exit_code;
    int     is_running;

} shell_state_t;

extern shell_state_t *global_state;

void shell_init(shell_state_t *state);
void execute_interactive_mode(shell_state_t *state);
void signal_handler(int signo);
void shell_cleanup(shell_state_t *state);

#endif //SHELL_H