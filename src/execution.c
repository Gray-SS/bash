#include "shell.h"
#include "execution.h"

int execute_command(command_t *cmd) {
    const char *name = cmd->args[0];

    if (is_builtin(name)) {
        return execute_builtin_command(cmd);
    }

    pid_t pid = execute_external_command(cmd);

    if (pid < 0) {
        return EXIT_FAILURE;
    }

    //TODO: Add an execute background functionality

    int status;
    waitpid(pid, &status, 0);

    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    } else {
        return EXIT_FAILURE;
    }

    fprintf(stderr, "No command found with name '%s'.\n", name);
    return 1;
}

pid_t execute_external_command(command_t *cmd) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return -1;
    } else if (pid == 0) {
        execvp(cmd->args[0], cmd->args);

        fprintf(stderr, "impossible to execute %s: %s\n", cmd->args[0], strerror(errno));
        exit(EXIT_FAILURE);
    }

    return pid;
}