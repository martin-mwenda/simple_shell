#include "shell.h"

/**
 * environ_ll - create from environ varisbles a linked list
 * @env: Environmental variables.
 * Return: Linked list.
 */
myli_t *environ_ll(char **env).
{
	myli_t *head;
	int i = 0;

	head = NULL;
	while (env[i] != NULL)
	{
		addEndNode(&head, env[i]);
		i++;
	}
	return (head);
}

/**
 * pr_env - Prints environmental variables.
 * @command: User's command into the shell
 * @envList: Environmental variables linked list.
 * Return: 0 on success.
 */
int pr_env(char **command, myli_t *envList)
{
	fr_dbptr(command);
	printList(envList);
	return (0);
}
