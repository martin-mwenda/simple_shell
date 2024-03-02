#include "shell.h"

/**
 * space_ig - Custom function to ignore leading spaces and newlines in a string
 * @input: Input string containing environmental variables
 * Return: Pointer to the modified string
 */
char *space_ig(char *input)
{
	while (*input == ' ' || *input == '\n')
		input++;
	return (input);
}

/**
 * not_inter - handles when user pipes commands into shell via pipeline
 * @env: envrionmental variables
 */
void not_inter(myli_t *env)
{
	size_t i = 0, n = 0;
	int command_line_no = 0, exit_stat = 0;
	char *command = NULL, *n_command = NULL, **n_line, **token;

	i = get_line(&command);
	if (i == 0)
	{
		free(command);
		exit(0);
	}
	n_command = command;
	command = space_ig(command);
	n_line = token_zer(command, "\n");
	if (n_command != NULL)
		free(n_command);
	n = 0;
	while (n_line[n] != NULL)
	{
		command_line_no++;
		token = NULL;
		token = token_zer(n_line[n], " ");
		exit_stat = built_in(token, env, command_line_no, n_line);
		if (exit_stat)
		{
			n++;
			continue;
		}
		exit_stat = _execve(token, env, command_line_no);
		n++;
	}
	fr_dbptr(n_line);
	fr_linkl(env);
	exit(exit_stat);
}

