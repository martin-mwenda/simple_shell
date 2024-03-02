#include "shell.h"

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
 * ex_ct - Frees resources and exits the main program with a specified value.
 * @str: User's command for the shell exit
 * @env: Environmental variables to free in case of an error.
 * @num: The user's command line input to print error message.
 * @command: The command arguments to free.
 * Return: 0 if successful, 2 if failure.
 */
int ex_ct(char **str, myli_t *env, int num, char **command)
{
	int e_value = 0;

	if (str[1] != NULL)
		e_value = custi(str[1]);
	if (e_value == -1)
	{
		illegal_numb(str[1], num, env);
		fr_dbptr(str);
		return (2);
	}
	fr_dbptr(str);
	fr_linkl(env);
	if (command != NULL)
	{
		fr_dbptr(command);
	}
	exit(e_value);
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
 * @env: Environmental variable linked list.
 * @name: Environmental variable name
 * @dir: Directory path
 *  Return: 0 on success
 */
int con_set(myli_t **env, char *name, char *dir)
{
	int index = 0, j = 0;
	char *cat;
	myli_t *holder;

	cat = dup_s(name);
	cat = st_cat(cat, "=");
	cat = st_cat(cat, dir);
	index = find_env(*env, name);
	holder = *env;
	while (j < index)
	{
		holder = holder->next;
		j++;
	}
	free(holder->var);
	holder->var = dup_s(cat);
	free(cat);
	return (0);
}

/**
 * exe_cd - Executes the 'cd' command.
 * @envList: Environmental linked list to update
 * @curDir: Current working directory.
 * @newDir: Directory path to change to.
 * @erMsg: 1st argument to write out error.
 * @liNum: Line number to write out error.
 * Return: 0 if success, 2 if fail
 */
int exe_cd(myli_t *envList, char *curDir, char *newDir, char *erMsg, int liNum)
{
	int status = 0;

	if (access(newDir, F_OK) == 0)
	{
		con_set(&envList, "OLDPWD", curDir);
		free(curDir);
		chdir(newDir);
		curDir = NULL;
		curDir = getcwd(curDir, 0);
		con_set(&envList, "PWD", curDir);
		free(curDir);
	}
	else
	{
		cantchange_dir(erMsg, liNum, envList);
		free(curDir);
		status = 2;
	}
	return (status);
}

