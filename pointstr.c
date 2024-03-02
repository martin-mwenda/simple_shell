#include "shell.h"

/**
 *  fr_dbptr - Free dynamically allocated memory for an array of strings.
 *  @stringArray: Array of strings.
 */
void fr_dbptr(char **stringArray)
{
	int i = 0;

	while (stringArray[i] != NULL)
	{
		free(stringArray[i]);
		i++;
	}
	free(stringArray);
}

/**
 * zero_count - counts number of 0s in a tens power number
 * @number: The number to count digits for.
 * Return: The count of digits.
 */
int zero_count(int number)
{
	int digitCount = 0;
	int num = number;

	while (num > 9 || num < -9)
	{
		num /= 10;
		digitCount++;
	}
	return (digitCount);
}

/**
 * con_atos - Converts an integer to a string.
 * @number: The integer to be converted.
 * Return: Returns the integer as a string. Returns NULL if failed.
 */
char *con_atos(int number)
{
	int digits, tens, i = 0, isNegative = 0, x;
	char *result;

	digits = number;
	tens = 1;
	if (number < 0)
	{
		isNegative = 1;
		digits *= -1;
	}
	result = malloc(sizeof(char) * (zero_count(digits) + 2 + isNegative));
	if (result == NULL)
		return (NULL);
	if (isNegative)
	{
		result[i] = '-';
		i++;
	}
	for (x = 0; digits > 9; x++)
	{
		digits /= 10;
		tens *= 10;
	}
	for (digits = number; x >= 0; x--)
	{
		result[i] = (digits / tens) + '0';
		i++;
		digits %= tens;
		tens /= 10;
	}
	result[i] = '\0';
	return (result);
}


