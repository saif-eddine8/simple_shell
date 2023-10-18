#include "shell.h"
/**
 * execute_cmd - command
 * @command: An array of command arguments
 * @argv: An array of arguments for the shell program
 * @idx: An index indicating the position of the command
 * Return: 127.
 */
int execute_cmd(char **command, char **argv, int idx)
{
	char *path_cmd = NULL;
	int status;
	pid_t pid;

	path_cmd = getpath(command[0]);
	if (path_cmd == NULL)
	{
		printError(argv[0], idx, command[0]);
		free_2(command);
		return (127);
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(path_cmd, command, environ) == -1)
		{
			free_2(command);
			free(path_cmd);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		free(path_cmd);
		free_2(command);
	}

	return (WEXITSTATUS(status));
}
