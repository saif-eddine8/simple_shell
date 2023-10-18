#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "shell.h"

int main(void) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while (1) {
        char prompt[] = "$ ";
        write(STDOUT_FILENO, prompt, 2); // Display the prompt

        read = custom_getline(&line, &len, stdin);
        if (read == -1) {
            if (feof(stdin)) {
                char newline = '\n';
                write(STDOUT_FILENO, &newline, 1); // Handle Ctrl+D
                free_dynamically_allocated_memory(line);
                _exit(0);
            } else {
                char error[] = "exception occurred\n";
                write(STDERR_FILENO, error, 19); // Handle errors
                free_dynamically_allocated_memory(line);
                _exit(1);
            }
        }

        line[read - 1] = '\0'; // Remove the trailing newline
       

        if (strcmp(line, "env") == 0) {
            print_environment();
        } 
        
        // Check if the input is "exit" and exit if true
        else if (strcmp(line, "exit") == 0) {
            free_dynamically_allocated_memory(line);
            _exit(0); // Exit the program
        }
        
        else {
             // Check if the command starts with /bin/
            if (strncmp(line, "/bin/", 5) != 0) {
            char full_path[256]; // Adjust the size as needed
            snprintf(full_path, sizeof(full_path), "/bin/%s", line);
            strcpy(line, full_path);
            }

        // Split command from arguments
        char *command = strtok(line, " ");
        char *args = strtok(NULL, "\0");

        // Check if the command exists and is executable
        if (access(command, X_OK) == -1) {
            char error[] = "No such file or directory\n";
            write(STDERR_FILENO, error, 26); // Handle command not found error
            continue; // Skip forking a child process
        }

        pid_t child_pid = fork();

        if (child_pid == -1) {
            char error[] = "process creation error\n";
            write(STDERR_FILENO, error, 23); // Handle fork error
            free_dynamically_allocated_memory(line);
            _exit(1);
        }

        if (child_pid == 0) {
            char *token;
            char *exec_args[32];  // Adjust the size as needed
            int arg_count = 1; // Include the command itself

            exec_args[0] = command;

            // Tokenize arguments
            token = strtok(args, " ");
            while (token != NULL) {
                exec_args[arg_count] = token;
                arg_count++;
                token = strtok(NULL, " ");
            }

            exec_args[arg_count] = NULL;  // Null-terminate the argument array

            execve(exec_args[0], exec_args, environ); // Use environ

            char error[] = "No such file or directory\n";
            write(STDERR_FILENO, error, 26); // Handle execve errors
            free_dynamically_allocated_memory(line);
            _exit(1);
        } else {
            wait(NULL); // Wait for the child to finish
        }
    }
    }

    free_dynamically_allocated_memory(line);
    return 0;
}
