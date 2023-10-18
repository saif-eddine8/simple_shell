#include "shell.h"
/**
 * spliter - to Split a string into an array of tokens
 * @line: is The string to split
 * Return: An array of tokens.
 */
char **spliter(char *line)
{
	int i = 0, j = 0;
	char *token, *tmp, **array = NULL;

	if (line == NULL)
		return (NULL);

	tmp = strdup(line);
	token = strtok(tmp, DELIM);
	if (!token)
	{
		free(line), free(tmp);
		return (NULL);
	}
	while (token)
	{
		j++;
		token = strtok(NULL, DELIM);
	}
	free(tmp);
	array = malloc(sizeof(char *) * (j + 1));
	token = strtok(line, DELIM);
	while (token)
	{
		array[i++] = strdup(token);
		token = strtok(NULL, DELIM);
	}
	free(line);
	array[i] = NULL;
	return (array);
}
