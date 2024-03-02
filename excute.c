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
	ex_tc(0);
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
 * @buffer: Buffer to store the user's command.
 * Return: Number of characters read.
 */
size_t get_line(char **buffer)
{
	ssize_t bytesRead = 0, totalSize = 0, terLp = 0, newlineFound = 0;
	char chunk[1024];

	while (terLp == 0 && (bytesRead = read(STDIN_FILENO, chunk, 1024 - 1)))
	{
		if (bytesRead == -1)
			return (-1);
		chunk[bytesRead] = '\0';

		newlineFound = 0;
		size_t n = 0;

		while (chunk[n] != '\0')
		{
			if (chunk[n] == '\n')
				newlineFound = 1;
			n++;
		}
		if (totalSize == 0)
		{
			bytesRead++;
			*buffer = malloc(sizeof(char) * bytesRead);
			*buffer = copy_str(*buffer, chunk);
			totalSize = bytesRead;
		}
		else
		{
			totalSize += bytesRead;
			*buffer = st_cat(*buffer, chunk);
		}
		terLp = newlineFound;
	}
	return (totalSize);
}

