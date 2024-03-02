#include "shell.h"

/**
 * main - creates a simple shell
 * @argc: Argument count
 * @argv: Argument vectors
 * @envp: Environmental variables
 * Return: 0 on success
 */
int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	prompt(envp);
	return (0);
}

