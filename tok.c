#include "shell.h"

/**
 * leng_str - the length of a token's string for dynamic memory allocation.
 * @str: A token.
 * @pos: Index position in the user's command typed into the shell.
 * @delm: Delimiter
 * Return: The length of the token's string.
 */
int leng_str(char *str, int pos, char delm)
{
	int len = 0;

	while ((str[pos] != delm) && (str[pos] != '\0'))
	{
		pos++;
		len++;
	}
	return (len);
}

/**
 * count_del - Count the number of delimiters in the string
 * @str: The user's command typed into the shell.
 * @delim: Delimiter character
 * Return: The number of delimiters
 */
int count_del(char *str, char delim)
{
	int i = 0, numDelimiters = 0;

	while (str[i] != '\0')
	{
		if ((str[i] == delim) && (str[i + 1] != delim))
		{
			numDelimiters++;
		}
		if ((str[i] == delim) && (str[i + 1] == '\0'))
		{
			numDelimiters--;
		}
		i++;
	}
	return (numDelimiters);
}
/**
 * rem_del - Returns a version of the string without preceding delimiters
 * @str: The input string.
 * @delim: Delimiter character
 * Return: A pointer to the new string
 */
char *rem_del(char *str, char delim)
{
	while (*str == delim)
	{
		str++;
	}
	return (str);
}

/**
 * token_zer - tokenizes a string and returns an array of tokens
 * @str: user's command typed into shell
 * @delm: delimeter
 * Return: an array of tokens
 */
char **token_zer(char *str, char *delm)
{
	int buffsize = 0, p = 0, si = 0, i = 0, len = 0, se = 0, t = 0;
	char **toks = NULL, d_ch;

	d_ch = delm[0];
	str = rem_del(str, d_ch);
	buffsize = count_del(str, d_ch);
	toks = malloc(sizeof(char *) * (buffsize + 2));
	if (toks == NULL)
		return (NULL);
	while (str[se] != '\0')
		se++;
	while (si < se)
	{
		if (str[si] != d_ch)
		{
			len = leng_str(str, si, d_ch);
			toks[p] = malloc(sizeof(char) * (len + 1));
			if (toks[p] == NULL)
				return (NULL);
			i = 0;
			while ((str[si] != d_ch) && (str[si] != '\0'))
			{
				toks[p][i] = str[si];
				i++;
				si++;
			}
			toks[p][i] = '\0';
			t++;
		}
		if (si < se && (str[si + 1] != d_ch && str[si + 1] != '\0'))
			p++;
		si++;
	}
	p++;
	toks[p] = NULL;
	return (toks);
}

/**
 * mcount_del - Return the number of tokens in the given string based on delim.
 * @str: The user's command typed into the shell.
 * @delim: Delimiter character
 * Return: The number of tokens.
 */
int mcount_del(char *str, char delim)
{
	int i = 0, numTokens = 0;

	while (str[i] != '\0')
	{
		if (str[i] == delim)
		{
			numTokens++;
		}
		i++;
	}
	return (numTokens);
}

