#include "shell.h"

/**
 * cant_find - Writes an error message
 * @user_command: User's typed command
 * @command_number: Nth user's typed command
 * @env: Environmental variables linked list to get shell name
 */
void cant_find(char *user_command, int command_number, myli_t *env)
{
	int count = 0;
	char *shell, *num;

	shell = br_env("_", env);
	while (shell[count] != '\0')
		count++;
	write(STDOUT_FILENO, shell, count);
	free(shell);
	write(STDOUT_FILENO, ": ", 2);
	num = con_atos(command_number);
	count = 0;
	while (num[count] != '\0')
		count++;
	write(STDOUT_FILENO, num, count);
	free(num);
	write(STDOUT_FILENO, ": ", 2);
	count = 0;
	while (user_command[count] != '\0')
		count++;
	write(STDOUT_FILENO, user_command, count);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, "not found\n", 10);
}

/**
 * cantchange_dir - write error
 * @str: user's typed argument after the cmd cd
 * @c_n: nth user's typed command
 * @env: bring in environmental variables linked list to write shell name
 */
void cantchange_dir(char *str, int c_n, myli_t *env)
{
	int count = 0;
	char *shell, *num;

	shell = br_env("_", env);
	while (shell[count] != '\0')
		count++;
	write(STDOUT_FILENO, shell, count);
	free(shell);
	write(STDOUT_FILENO, ": ", 2);
	num = con_atos(c_n);
	count = 0;
	while (num[count] != '\0')
		count++;
	write(STDOUT_FILENO, num, count);
	free(num);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, "cd: can't cd to ", 16);
	count = 0;
	while (str[count] != '\0')
	count++;
	write(STDOUT_FILENO, str, count);
	write(STDOUT_FILENO, "\n", 1);
}

/**
 * illegal_numb - Writes an error message
 * @argument: User's typed argument after the "exit" command
 * @command_number: Nth user's typed command
 * @env: Environmental variables linked list to get shell name
 */
void illegal_numb(char *argument, int command_number, myli_t *env)
{
	int count = 0;
	char *shell = NULL, *num = NULL;

	shell = br_env("_", env);
	while (shell[count] != '\0')
		count++;
	write(STDOUT_FILENO, shell, count);
	free(shell);
	write(STDOUT_FILENO, ": ", 2);
	num = con_atos(command_number);
	count = 0;
	while (num[count] != '\0')
		count++;
	write(STDOUT_FILENO, num, count);
	free(num);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, "exit: Illegal number: ", 22);
	count = 0;
	while (argument[count] != '\0')
		count++;
	write(STDOUT_FILENO, argument, count);
	write(STDOUT_FILENO, "\n", 1);
}

