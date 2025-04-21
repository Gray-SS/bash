#include "shell.h"

int main(void) {
    shell_state_t state;

    shell_init(&state);
    execute_interactive_mode(&state);
    shell_cleanup(&state);

    return state.exit_code;
}