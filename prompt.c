#include "shell.h"

/**
 * ctrl_c - Function to handle Ctrl-C signal, ignoring the input and printing
 * @signal: Integer representing the signal received
 */
void ctrl_c(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n$ ", 3);
}

/**
 * ignore_space - Returns a new string without leading spaces
 * @input: Input string
 * Return: New string with leading spaces removed
 */
char *ignore_space(char *input)
{
	while (*input == ' ')
		input++;
	return (input);
}

/**
 * ctrl_D - Exits the program if Ctrl-D was pressed
 * @characters_read: Characters read via get_line
 * @user_command: User's typed-in command
 * @env: Environmental variable linked list
 */
void ctrl_D(int characters_read, char *user_command, myli_t *env)
{
	if (characters_read == 0)
	{
		free(user_command);
		fr_linkl(env);
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
}

/**
 * prompt - repeatedly prompts user and executes user's cmds if applicable
 * @en: envrionmental variables
 * Return: 0 on success
 */
int prompt(char **en)
{
	myli_t *env;
	size_t i = 0, n = 0;
	int command_line_no = 0, exit_stat = 0;
	char *command, *n_command, **token;

	env = environ_ll(en);
	do {
		command_line_no++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);
		else
			not_inter(env);
		signal(SIGINT, ctrl_c);
		command = NULL;
		i = 0;
		i = get_line(&command);
		ctrl_D(i, command, env);
		n_command = command;
		command = ignore_space(command);
		n = 0;
		while (command[n] != '\n')
			n++;
		command[n] = '\0';
		if (command[0] == '\0')
		{
			free(n_command);
			continue;
		}
		token = NULL;
		token = token_zer(command, " ");
		if (n_command != NULL)
			free(n_command);
		exit_stat = built_in(token, env, command_line_no, NULL);
		if (exit_stat)
			continue;
		exit_stat = _execve(token, env, command_line_no);
	} while (1);
	return (exit_stat);
}

/**
 * built_in - handles builtins
 * @token: user's typed command
 * @env: environmental variable
 * @num: take in nth user command typed to write error message
 * @command: bring in command to free
 * Return: 1 if acted on builtin, 0 if not
 */
int built_in(char **token, myli_t *env, int num, char **command)
{
	int i = 0;

	if (comp_str(token[0], "exit") == 0)
	{
		i = ex_tc(token, env, num, command);
	}
	else if (comp_str(token[0], "env") == 0)
	{
		pr_env(token, env);
		i = 1;
	}
	else if (comp_str(token[0], "cd") == 0)
	{
		i = c_d(token, env, num);
	}
	else if (comp_str(token[0], "setenv") == 0)
	{
		put_env(&env, token);
		i = 1;
	}
	else if (comp_str(token[0], "unsetenv") == 0)
	{
		unput_env(&env, token);
		i = 1;
	}
	return (i);
}


