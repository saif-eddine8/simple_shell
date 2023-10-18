#include "shell.h"
/**
 * my_getenv - a function
 * @variable: a  pointer
 * Return: a pointer
 */
char *my_getenv(char *variable)
{
	int i;
	char *key, *env, *temp;

	for (i = 0; environ[i]; i++)
	{
		temp = strdup(environ[i]);
		key = strtok(temp, "=");
		if (strcmp(key, variable) == 0)
		{
			env = strdup(strtok(NULL, "\n"));
			free(temp);
			return (env);
		}
		free(temp);
	}
	return (NULL);
}
/**
 * free_2 - a function
 * @array: a  pointer
 * Return: a pointer
 */
void free_2(char **array)
{
	int i;

	if (!array)
		return;

	for (i = 0; array[i]; i++)
	{
		free(array[i]);
		array[i] = NULL;
	}
	free(array), array = NULL;
}
/**
 * printError - Print an error message to standard error
 * @name: A pointer to a program name
 * @idx: An index value
 * @command: A pointer to the command causing the error
 */
void printError(char *name, int idx, char *command)
{
	char *index;
	char message[] = ": not found\n";

	index = _itoa(idx);

	write(STDERR_FILENO, name, strlen(name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, index, strlen(index));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, command, strlen(command));
	write(STDERR_FILENO, message, strlen(message));
	free(index);
}
/**
 * _itoa - a function
 * @n: integer
 * Return: a pointer
 */
char *_itoa(int n)
{
	char buffer[20], tmp;
	int i = 0, start = 0, end;

	if (n == 0)
		buffer[i++] = '0';
	else
	{
		while (n > 0)
		{
			buffer[i++] = (n % 10) + '0';
			n /= 10;
		}
	}
	buffer[i] = '\0';
	/* reverse buffer */
	end = i - 1;
	while (start < end)
	{
		tmp = buffer[start];
		buffer[start] = buffer[end];
		buffer[end] = tmp;
		start++;
		end--;
	}
	return (strdup(buffer));
}
