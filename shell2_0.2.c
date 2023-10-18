#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

extern char **environ;

int main(void) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while (1) {
        char prompt[] = "$ ";
        write(STDOUT_FILENO, prompt, 2); // Display the prompt

        read = getline(&line, &len, stdin);
        if (read == -1) {
            if (feof(stdin)) {
                char newline = '\n';
                write(STDOUT_FILENO, &newline, 1); // Handle Ctrl+D
                free(line);
                _exit(0);
            } else {
                char error[] = "exception occurred\n";
                write(STDERR_FILENO, error, 19); // Handle errors
                free(line);
                _exit(1);
            }
        }

        line[read - 1] = '\0'; // Remove the trailing newline

        pid_t child_pid = fork();

        if (child_pid == -1) {
            char error[] = "process creation error\n";
            write(STDERR_FILENO, error, 23); // Handle fork error
            free(line);
            _exit(1);
        }

        if (child_pid == 0) {
            char *token;
            char *args[32];  // Adjust the size as needed
            int arg_count = 0;

            token = strtok(line, " ");
            while (token != NULL) {
                args[arg_count] = token;
                arg_count++;
                token = strtok(NULL, " ");
            }
            args[arg_count] = NULL;  // Null-terminate the argument array

            execve(args[0], args, environ); // Use environ

            char error[] = "No such file or directory\n";
            write(STDERR_FILENO, error, 26); // Handle execve errors
            free(line);
            _exit(1);
        } else {
            wait(NULL); // Wait for the child to finish
        }
    }

    free(line);
    return 0;
}
