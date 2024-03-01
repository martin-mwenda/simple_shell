

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
 * @delim: delimeter
 * Return: an array of tokens
 */
char **token_zer(char *str, char *delim)
{
	int bufferSize = 0, p = 0, st = 0, i = 0, len = 0;
	int enex = 0, tokenCount = 0;
	char **tokens = NULL, del;

	del = delim[0];
	str = rem_del(str, del);
	buffersize = count_del(str, del);
	tokens = malloc(sizeof(char *) * (bufferSize + 2));
	if (tokens == NULL)
		return (NULL);
	while (str[enex] != '\0')
		enex++;
	while (st < enex)
	{
		if (str[st] != del)
		{
			len = leng_str(str, st, del);
			tokens[p] = malloc(sizeof(char) * (len + 1));
			if (tokens[p] == NULL)
				return (NULL);
			i = 0;
			while ((str[st] != del) && (str[st] != '\0'))
			{
				tokens[p][i] = str[st];
				i++;
				st++;
			}
			tokens[p][i] = '\0';
			tokenCount++;
		}
		if (st < enex && (str[st + 1] != del && str[st + 1] != '\0'))
			st++;
	}
	p++;
	tokens[p] = NULL;
	return (tokens);
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

