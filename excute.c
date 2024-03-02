#include "shell.h"

/**
 * cm_frexit - Frees user's typed command and linked list before exiting.
 * @cmd: User's typed command.
 * @envList: Input the linked list of environment
 */
void cm_frexit(char **cmd, myli_t *envList)
{
	fr_dbptr(cmd);
	fr_linkl(envList);
	ex_ct(NULL, NULL, 0, NULL);
}

/**
 * _execve - Execute command user typed into shell.
 * @command: Command user typed
 * @envList: Environmental variable.
 * @num: Nth user command; to be used in the error message.
 * Return: 0 on success.
 */
int _execve(char **command, myli_t *envList, int num)
{
	char *executable;
	int status = 0, isAbsolute = 0;
	pid_t pid;

	if (access(command[0], F_OK) == 0)
	{
		executable = command[0];
		isAbsolute = 1;
	}
	else
	{
		executable = w_hch(command[0], envList);
	}
	if (access(executable, X_OK) != 0)
	{
		cant_find(command[0], num, envList);
		fr_dbptr(command);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(executable, command, NULL) == -1)
			{
				cant_find(command[0], num, envList);
				cm_frexit(command, envList);
			}
		}
		else
		{
			wait(&status);
			fr_dbptr(command);
			if (isAbsolute == 0)
				free(executable);
		}
	}
	return (0);
}

/**
 * get_line - Stores into a malloced buffer the user's command into the shell.
 * @str: Buffer to store the user's command.
 * Return: Number of characters read.
 */
size_t get_line(char **str)
{
	ssize_t i = 0, size = 0, t = 0, t2 = 0, n = 0;
	char buff[1024];

	while (t2 == 0 && (i = read(STDIN_FILENO, buff, 1024 - 1)))
	{
		if (i == -1)
			return (-1);
		buff[i] = '\0';
		n = 0;
		while (buff[n] != '\0')
		{
			if (buff[n] == '\n')
				t2 = 1;
			n++;
		}
		if (t == 0)
		{
			i++;
			*str = malloc(sizeof(char) * i);
			*str = copy_str(*str, buff);
			size = i;
			t = 1;
		}
		else
		{
			size += i;
			*str = st_cat(*str, buff);
		}
	}
	return (size);
}

