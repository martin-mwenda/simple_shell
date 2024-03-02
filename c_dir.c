#include "shell.h"

/**
 * c_dir - Change the current directory to the home directory.
 * @envList: Environmental linked list to update PATH and OLDPWD.
 * @currentDir: Current working directory.
 */
void c_dir(myli_t *envList, char *currentDir)
{
	char *home = NULL;

	home = br_env("HOME", envList);
	con_set(&envList, "OLDPWD", currentDir);
	free(currentDir);
	if (access(home, F_OK) == 0)
		chdir(home);
	currentDir = NULL;
	currentDir = getcwd(currentDir, 0);
	con_set(&envList, "PWD", currentDir);
	free(currentDir);
	free(home);
}

/**
 * c_d - change dir
 * @str: user's typed in command
 * @envList: Environmental linked list to retrieve HOME and OLDPWD paths
 * @num: Nth user command, to be used in error message.
 * Return: 0 if success, 2 if failed.
 */
int c_d(char **str, myli_t *envList, int num)
{
	char *current = NULL, *dir = NULL;
	int exitStat = 0;

	current = getcwd(current, 0);
	if (str[1] != NULL)
	{
		if (str[1][0] == '~')
		{
			dir = br_env("HOME", envList);
			dir = conc_s(dir, str[1]);
		}
		else if (str[1][0] == '-')
		{
			if (str[1][1] == '\0')
				dir = br_env("OLDPWD", envList);
		}
		else
		{
			if (str[1][0] != '/')
			{
				dir = getcwd(dir, 0);
				dir = st_cat(dir, "/");
				dir = st_cat(dir, str[1]);
			}
			else
			{
				dir = dup_s(str[1]);
			}
		}
		exitStat = exe_cd(envList, current, dir, str[1], num);
		free(dir);
	}
	else
		c_dir(envList, current);
	fr_dbptr(str);
	return (exitStat);
}
