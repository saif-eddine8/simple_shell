#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define DELIM " \n\t"

extern char **environ;

/**
 * struct list_dir - singly linked list
 * @dir: directory
 * @next: points to the next node
 * Description: singly linked list node structure
 */
typedef struct list_dir
{
	char *dir;
	struct list_dir *next;
} list_dir;


/* input_line.c */
char *get_line(void);

/* spliter.c */
char **spliter(char *line);

/* execute.c */
int execute_cmd(char **command, char **argv, int idx);

/* getpath.c */
list_dir *build_path_list(void);
char *getpath(char *command);

/* getenv.c*/
char *my_getenv(char *variable);

/* bultins */
void my_printenv(char **command, int *status);
void my_exit_shell(char **command, int *status);

/* tools.c */
char *_itoa(int n);
void free_2(char **array);
void printError(char *name, int idx, char *command);

/* linked_list */
list_dir *add_node_end(list_dir **head, const char *str);
void free_list_dir(list_dir *head);

#endif
