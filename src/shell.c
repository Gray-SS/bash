#include "shell.h"

shell_state_t *global_state = NULL;

void shell_init(shell_state_t *state) {
    state->exit_code = 0;
    state->is_running = 1;
    state->is_root = 0;
    state->last_command_status = 0;

    state->username = getenv("USER");
    if (!state->username) {
        state->username = "user";
    }

    char hostname[MAX_HOSTNAME_LENGTH];
    if (gethostname(hostname, MAX_HOSTNAME_LENGTH) == 0) {
        state->hostname = strdup(hostname);
    } else {
        state->hostname = strdup("localhost");
    }

    if (!getcwd(state->crnt_dir, MAX_PATH_LENGTH)) {
        strcpy(state->crnt_dir, ".");
    }

    global_state = state;
    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);
}

void display_prompt(shell_state_t *state) {
    char *home_dir = getenv("HOME");
    char formatted_dir[MAX_PATH_LENGTH];
    strcpy(formatted_dir, state->crnt_dir);

    if (home_dir && strncmp(formatted_dir, home_dir, strlen(home_dir)) == 0) {
        char temp[MAX_PATH_LENGTH];
        sprintf(temp, "~%s", formatted_dir + strlen(home_dir));
        strcpy(formatted_dir, temp);
    }

    if (state->last_command_status == 0) {
        printf("%s✓%s ", COLOR_SUCCESS, COLOR_RESET);
    } else if (state->last_command_status > 0) {
        printf("%s✗%s ", COLOR_ERROR, COLOR_RESET);
    }

    printf("%s%s%s@%s%s%s:%s%s%s %s%s%s ",
           COLOR_BOLD, COLOR_USER, state->username,
           COLOR_HOST, state->hostname, COLOR_RESET,
           COLOR_DIR, formatted_dir, COLOR_RESET,
           COLOR_PROMPT, state->is_root ? "#" : "$", COLOR_RESET);

    fflush(stdout);
}


void execute_interactive_mode(shell_state_t *state) {
    char input[MAX_INPUT_SIZE];

    while (state->is_running) {
        display_prompt(state);

        if (!fgets(input, MAX_INPUT_SIZE, stdin)) {
            if (feof(stdin)) {
                printf("\n");
                break;
            }
            continue;
        }

        input[strcspn(input, "\n")] = '\0';

        command_t *cmd = parse_command(input);
        if (!cmd) continue;

        state->last_command_status = execute_command(cmd);
        printf("\n");

        free_command(cmd);
    }
}

void shell_cleanup(shell_state_t *state) {
    free(state->hostname);
}

void signal_handler(int signo) {
    if (!global_state) {
        return;
    }

    if (signo == SIGINT) {
        printf("\n");
        display_prompt(global_state);
        fflush(stdout);
    }
    else if (signo == SIGTERM) {
        global_state->is_running = 0;
        write(STDOUT_FILENO, "\nExiting...\n", 12);
    }
}