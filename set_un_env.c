#include "shell.h"

/**
 * find_env - Finds the given environmental variable in the linked list
 * @env: Linked list of environmental variables
 * @variable_name: Name of the variable to find
 * Return: Index of the node in the linked list, or -1 if not found
 */
int find_env(myli_t *env, char *variable_name)
{
	int j = 0, index = 0;

	while (env != NULL)
	{
		j = 0;
		while ((env->var)[j] == variable_name[j])
			j++;
		if (variable_name[j] == '\0')
			break;
		env = env->next;
		index++;
	}
	if (env == NULL)
		return (-1);
	return (index);
}

/**
 * unput_env - Removes a node in the environmental linked list
 * @env: Linked list of environmental variables
 * @str: User's typed-in command
 * Return: 0 on success, -1 on failure
 */
int unput_env(myli_t **env, char **str)
{
	int index = 0, delete_status = 0;

	if (str[1] == NULL)
	{
		write(STDOUT_FILENO, "Too few arguments\n", 18);
		fr_dbptr(str);
		return (-1);
	}
	index = find_env(*env, str[1]);
	fr_dbptr(str);
	if (index == -1)
	{
		write(STDOUT_FILENO, "Cannot find\n", 12);
		return (-1);
	}
	delete_status = del_node_index(env, index);
	if (delete_status == -1)
	{
		write(STDOUT_FILENO, "Cannot find\n", 12);
		return (-1);
	}
	return (0);
}

/**
 * put_env - create or modify existing environmental variable in linked list
 * @env: linked list
 * @str: user's typed in command
 * Return: 0 on success, 1 on fail
 */
int put_env(myli_t **env, char **str)
{
	int index = 0, j = 0;
	char *cat;
	myli_t *holder;

	if (str[1] == NULL || str[2] == NULL)
	{
		write(STDOUT_FILENO, "Too few arguments\n", 18);
		fr_dbptr(str);
		return (-1);
	}
	cat = dup_s(str[1]);
	cat = st_cat(cat, "=");
	cat = st_cat(cat, str[2]);
	index = find_env(*env, str[1]);
	if (index == -1)
	{
		add_endde(env, cat);
	}
	else
	{
		holder = *env;
		while (j < index)
		{
			holder = holder->next;
			j++;
		}
		free(holder->var);
		holder->var = dup_s(cat);
	}
	free(cat);
	fr_dbptr(str);
	return (0);
}

