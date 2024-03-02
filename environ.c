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

/**
 * str_dup - Custom string duplication, excluding beginning bytes
 * @str: String to duplicate
 * @excludeBytes: Number of bytes to exclude
 * Return: Duplicated string
 */
char *str_dup(char *str, int excludeBytes)
{
	char *duplicateStr;
	int i, len = 0;

	if (str == NULL)
		return (NULL);
	while (*(str + len))
		len++;
	len++;
	duplicateStr = malloc(sizeof(char) * (len - excludeBytes));
	if (duplicateStr == NULL)
		return (NULL);
	i = 0;
	while (i < (len - excludeBytes))
	{
		*(duplicateStr + i) = *(str + excludeBytes + i);
		i++;
	}
	return (duplicateStr);
}

/**
 * br_env - Finds and returns a copy of the requested environmental variable.
 * @variableTitle: String to store it in.
 * @envList: Entire set of environmental variables.
 * Return: Copy of the requested environmental variable.
 */
char *br_env(char *variableTitle, myli_t *envList)
{
	int j = 0, titleLength = 0;

	while (envList != NULL)
	{
		j = 0;
		while ((envList->var)[j] == variableTitle[j])
			j++;
		if (variableTitle[j] == '\0' && (envList->var)[j] == '=')
			break;
		envList = envList->next;
	}
	while (variableTitle[titleLength] != '\0')
		titleLength++;
	titleLength++;
	return (str_dup(envList->var, titleLength));
}

