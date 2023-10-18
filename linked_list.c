#include "shell.h"

/**
 * add_node_end - a function that adds a new node at the end of list.
 * @head: a list_dir list.
 * @str: the element to add.
 * Return: the address of the new element, or NULL if it faile.
 */
list_dir *add_node_end(list_dir **head, const char *str)
{
	list_dir *new_node, *tmp;

	if (head == NULL || str == NULL)
		return (NULL);

	new_node = malloc(sizeof(list_dir));
	if (new_node == NULL)
		return (NULL);

	new_node->dir = strdup(str);
	if (new_node->dir == NULL)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	if (*head == NULL)
	{
		*head = new_node;
		return (*head);
	}

	tmp = *head;
	while (tmp->next != NULL)
		tmp = tmp->next;

	tmp->next = new_node;
	return (*head);
}

/**
 * free_list_dir - Frees a list_dir list
 * @head: Start of the list
 * Return: (void)
 */
void free_list_dir(list_dir *head)
{
	list_dir *tmp;

	if (head == NULL)
		return;
	while (head != NULL)
	{
		tmp = head->next;
		free(head->dir);
		free(head);
		head = tmp;
	}
}
