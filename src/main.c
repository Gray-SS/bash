#include "shell.h"

int main(void) {
    shell_state_t state;

    shell_init(&state);
    return execute_interactive_mode(&state);
}