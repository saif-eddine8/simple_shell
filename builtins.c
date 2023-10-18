#include "shell.h"
/**
 * my_printenv - to Print the environment variables
 * @command: An array of command arguments
 * @status: A pointer to the status code
 */
void my_printenv(char **command, int *status)
{
	int i;

	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	(*status) = 0;
	free_2(command);
}
/**
 * my_exit_shell - Exit the shell
 * @command: An array of command arguments
 * @status: A pointer to the status code
 */
void my_exit_shell(char **command, int *status)
{
	int exit_status = *status;

	free_2(command);
	exit(exit_status);
}
