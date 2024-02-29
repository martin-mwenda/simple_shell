include "shell.h"

/**
 * custi - Custom implementation that converts a string to an integer
 * @str: The input string.
 * Return: The converted integer if successful,
 *         -1 if the string contains non-numeric characters.
 */
int custi(char *str)
{
	int index = 0;
	unsigned int result = 0;

	while (str[index] != '\0')
	{
		if (str[index] >= '0' && str[index] <= '9')
			result = result * 10 + (str[index] - '0');
		if (str[index] > '9' || str[index] < '0')
			return (-1);
		index++;
	}
	return (result);
}

/**
 * ex_tc - Frees resources and exits the main program with a specified value.
 * @args: User's command for the shell exit
 * @envList: Environmental variables to free in case of an error.
 * @inputOrder: The user's command line input to print error message.
 * @commandArgs: The command arguments to free.
 * Return: 0 if successful, 2 if failure.
 */
int ex_tc(char **args, list_t *envList, int inputOrder, char **commandArgs)
{
	int exitValue = 0;


	if (args[1] != NULL)
		exitValue = custi(args[1]);
	if (exitValue == -1)
	{
		illegal_numb(args[1], inputOrder, envList);
		fr_dbPtr(args);
		return (2);
	}
	fr_dbPtr(args);
	fr_linkl(envList);

	if (commandArgs != NULL)
		fr_dbPtr(commandArgs);

	exit(exitValue);
}

/**
 * conc_s - Concatenate two strings ignoring the first character
 * @destination: String to be appended to
 * @source: String to append
 * Return: Concatenated string
 */
char *conc_s(char *destination, char *source)
{
	int destLen = 0;
	int srcLen = 0;
	int totalLen = 0;
	int j = 0;

	while (destination[destLen] != '\0')
	{
		destLen++;
		totalLen++;
	}
	while (source[srcLen] != '\0')
	{
		srcLen++;
		totalLen++;
	}
		destination = _realloc(destination, destLen, sizeof(char) * totalLen + 1);

		j = 1;
		while (source[j] != '\0')
		{
			destination[destLen] = source[j];
			destLen++;
			j++;
		}
		destination[destLen] = '\0';

		return (destination);
}

/**
 * con_set - by concatenating strings before setting.
 * @envList: Environmental variable linked list.
 * @name: Environmental variable name
 * @directory: Directory path
 *  Return: 0 on success
 */
int con_set(list_t **envList, char *name, char *directory)
{
	int index = 0, j = 0;
	char *concatenatedString;
	myli_t *holder;

	concatenatedString = dup_s(name);
	concatenatedString = st_cat(concatenatedString, "=");
	concatenatedString = st_cat(concatenatedString, directory);
	index = find_env(*envList, name);
	holder = *envList;
	while (j < index)
	{
		holder = holder->next;
		j++;
	}
	free(holder->var);
	holder->var = st_dup(concatenatedString);
	free(concatenatedString);
	return (0);
}

