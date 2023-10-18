#include "shell.h"

/**
 * build_path_list - Build a linked list of the PATH directories
 * Return: a linked list of the PATH directories.
*/
list_dir *build_path_list(void)
{
	list_dir *head = NULL;
	char *path_env, *token;

	path_env = my_getenv("PATH");
	if (!path_env)
		return (NULL);
	token = strtok(path_env, ":");
	while (token)
	{
		add_node_end(&head, token);
		token = strtok(NULL, ":");
	}
	free(path_env);
	return (head);
}

/**
 * getpath - Get the full path of a command
 * @command: the command to handle.
 * Return: the full path of the command.
*/
char *getpath(char *command)
{
	list_dir *ld, *tmp;
	char *path;
	struct stat st;
	int i;

	for (i = 0; command[i]; i++)
	{
		if (command[i] == '/')
		{
			if (stat(command, &st) == 0)
				return (strdup(command));
			else
				return (NULL);
		}
	}
	ld = build_path_list();
	tmp = ld;
	while (tmp)
	{
		path = malloc(strlen(tmp->dir) + strlen(command) + 2);
		if (!path)
		{
			free_list_dir(ld);
			return (NULL);
		}
		strcpy(path, tmp->dir);
		strcat(path, "/");
		strcat(path, command);
		if (stat(path, &st) == 0)
		{
			free_list_dir(ld);
			return (path);
		}
		free(path), path = NULL;
		tmp = tmp->next;
	}
	free_list_dir(ld);
	return (NULL);
}
