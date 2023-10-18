#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifndef SHELL_H
#define SHELL_H

extern char **environ;
size_t custom_strlen(const char *str);

// 'print_environment' function is used as the built-in 'env' version.
void print_environment() {
	char **env = environ;

	while (*env) {
		printf("%s\n", *env);
		env++;
	}
}

ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream) {
   if (lineptr == NULL || n == NULL) {
		return -1; // Return an error code for invalid arguments
	}

	size_t line_length = 0;
	char *line = *lineptr;
	int buffer_size = 128; // Initial buffer size

	while (1) {
		if (line_length >= *n) {
			// Increase the size of the line buffer
			buffer_size *= 2;
			char *new_line = (char *)realloc(*lineptr, buffer_size);
			if (new_line == NULL) {
				free(*lineptr); // Free the old buffer
				*lineptr = NULL; // Set to NULL to avoid double freeing
				return -1; // Return an error code for memory allocation failure
			}
			*lineptr = new_line;
			*n = buffer_size;
			line = *lineptr;
		}

		char c;
		ssize_t bytes_read = read(fileno(stream), &c, 1);

		if (bytes_read < 0) {
			return -1; // Return an error code for reading failure
		} else if (bytes_read == 0) {
			// End of file (Ctrl+D)
			if (line_length == 0) {
				return 0;
			} else {
				line[line_length] = '\0';
				return line_length;
			}
		} else {
			line[line_length] = c;
			line_length++;
			if (c == '\n') {
				line[line_length] = '\0';
				return line_length;
			}
		}
	}
}

void free_dynamically_allocated_memory(char *line) {
	if (line != NULL) {
		free(line);
	}
}

char *custom_strtok(char *str, const char *delim) {
	static char *pos = NULL;  // Static variable to maintain position

	if (str != NULL) {
		pos = str;
	}

	if (pos == NULL || *pos == '\0') {
		return NULL;
	}

	// Skip leading delimiters
	while (*pos != '\0' && strchr(delim, *pos) != NULL) {
		pos++;
	}

	if (*pos == '\0') {
		return NULL;
	}

	char *token = pos;

	while (*pos != '\0' && strchr(delim, *pos) == NULL) {
		pos++;
	}

	if (*pos != '\0') {
		*pos = '\0';
		pos++;
	}

	return token;
}

#endif
