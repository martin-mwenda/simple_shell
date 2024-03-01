#include "shell.h"

/**
 * comp_str - Compare two strings.
 * @str1: The first string to compare.
 * @str2: The second string to compare.
 * Return: An integer that represents the difference between the strings.
 *         0 if the strings are exactly the same.
 *         Positive value if str1 is greater than str2.
 *         Negative value if str1 is less than str2.
 */
int comp_str(char *str1, char *str2)
{
	int i = 0;

	while (*(str1 + i) == *(str2 + i) && *(str1 + i))
		i++;
	if (*(str2 + i))
		return (*(str1 + i) - *(str2 + i));
	else
		return (0);
}

/**
 * copy_str - Copy the string pointed to
 * @destination: Buffer to copy the source string to.
 * @source: Source string to copy.
 * Return: Pointer to the destination
 */
char *copy_str(char *destination, char *source)
{
	int i, len;

	for (len = 0; source[len] != '\0'; len++)
		;

	for (i = 0; i <= len; i++)
		destination[i] = source[i];
	return (destination);
}

/**
 * dup_s - Create a duplicate of the input string in allocated memory.
 * @str: The string to duplicate.
 * Return: Pointer to the duplicated string in allocated memory,
 *         or NULL if str is NULL or if memory allocation fails.
 */
char *dup_s(char *str)
{
	char *duplicateStr;
	int i, len = 0;

	if (str == NULL)
		return (NULL);
	while (*(str + len))
		len++;
	len++;
	duplicateStr = malloc(sizeof(char) * len);
	if (duplicateStr == NULL)
		return (NULL);
	i = 0;

	while (i < len)
	{
		*(duplicateStr + i) = *(str + i);
		i++;
	}
	return (duplicateStr);
}

