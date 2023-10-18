#include "shell.h"
/**
 * main - Entry points
 * @ac: a number of arg
 * @av: a double pointer of arg
 * Return: status
 */
int main(int ac, char **av)
{
	char *line = NULL, **command = NULL;
	int status = 0, index = 0;
	(void)ac;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		line = get_line();
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			return (status);
		}
		index++;
		command = spliter(line);
		if (!command)
			continue;

		if (strcmp(command[0], "exit") == 0)
			my_exit_shell(command, &status);

		else if (strcmp(command[0], "env") == 0)
			my_printenv(command, &status);

		else
			status = execute_cmd(command, av, index);
	}
}
