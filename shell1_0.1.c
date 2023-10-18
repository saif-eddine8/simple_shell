#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "shell.h"

int main(void) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while (1) {
        char prompt[] = "$ ";
        write(STDOUT_FILENO, prompt, sizeof(prompt) - 1); // Display the prompt

        read = getline(&line, &len, stdin);
        if (read == -1) {
            if (feof(stdin)) {
                char newline = '\n';
                write(STDOUT_FILENO, &newline, 1); // Handle Ctrl+D
                free(line);
                exit(0);
            } else {
                char *error = "exception occurred\n";
                write(STDERR_FILENO, error, strlen(error)); // Handle errors
                free(line);
                exit(1);
            }
        }

        line[read - 1] = '\0'; // Remove the trailing newline

        pid_t child_pid = fork();

        if (child_pid == -1) {
            char *error = "process creation error\n";
            write(STDERR_FILENO, error, strlen(error)); // Handle fork error
            free(line);
            exit(1);
        }

        if (child_pid == 0) {
            char *args[] = {line, NULL};
            if (execve(line, args, environ) == -1) {
                char *error = "No such file or directory\n";
                write(STDERR_FILENO, error, strlen(error)); // Handle execve errors
                free(line);
                exit(1);
            }
        } else {
            wait(NULL); // Wait for the child to finish
        }
    }

    free(line);
    return 0;
}