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

