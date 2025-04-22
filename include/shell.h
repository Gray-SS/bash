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

#include <readline/readline.h>
#include <readline/history.h>

#include "parser.h"
#include "execution.h"

#define HISTORY_PATH ".shell_history"

#define MAX_ARGS 256
#define MAX_INPUT_SIZE 4096
#define MAX_PATH_LENGTH 1024
#define MAX_HOSTNAME_LENGTH 256
#define DELIMITERS " \t\r\n\a"

// Codes de couleur ANSI
#define COLOR_RESET     "\033[0m"
#define COLOR_BOLD      "\033[1m"
#define COLOR_USER      "\033[38;5;39m"    // Bleu clair
#define COLOR_HOST      "\033[38;5;208m"   // Orange
#define COLOR_DIR       "\033[38;5;76m"    // Vert
#define COLOR_SUCCESS   "\033[38;5;46m"    // Vert vif
#define COLOR_ERROR     "\033[38;5;196m"   // Rouge vif
#define COLOR_PROMPT    "\033[38;5;226m"   // Jaune

typedef struct {
    char   *username;
    char   *hostname;
    char    crnt_dir[MAX_PATH_LENGTH];

    int     exit_code;
    int     is_running;
    int     is_root;
    int     last_command_status;

} shell_state_t;

extern shell_state_t *global_state;

void shell_init(shell_state_t *state);
void shell_cleanup(shell_state_t *state);

int execute_interactive_mode(shell_state_t *state);

void save_history();
void load_history();

void signal_handler(int signo);

#endif //SHELL_H