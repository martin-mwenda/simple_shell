#include "shell.h"

/**
 * c_str_tok - tokenizes a string even the continuous delim with empty string
 * @str: user's command typed into shell
 * @delm: delimeter
 * Return: an array of tokens
 */
char **c_str_tok(char *str, char *delm)
{
	int buffsize = 0, p = 0, si = 0, i = 0, len = 0, se = 0;
	char **toks = NULL, d_ch;

	d_ch = delm[0];
	buffsize = mcount_del(str, d_ch);
	toks = malloc(sizeof(char *) * (buffsize + 2));
	if (toks == NULL)
		return (NULL);
	while (str[se] != '\0')
		se++;
	while (si < se)
	{
		len = leng_str(str, si, d_ch);
		toks[p] = malloc(sizeof(char) * (len + 1));
		if (toks[p] == NULL)
			return (NULL);
		i = 0;
		while ((str[si] != d_ch) &&
				(str[si] != '\0'))
		{
			toks[p][i] = str[si];
			i++;
			si++;
		}
		toks[p][i] = '\0';
		p++;
		si++;
	}
	toks[p] = NULL;
	return (toks);
}

/**
 * w_hch - fleshes out command by appending it to a matching PATH directory
 * @str: first command user typed into shell
 * @env: environmental variable
 * Return: a copy of fleshed out command
 */
char *w_hch(char *str, myli_t *env)
{
	char *pth, *cat = NULL, **toks;
	int i = 0;

	pth = br_env("PATH", env);
	toks = c_str_tok(pth, ":");
	free(pth);
	i = 0;
	while (toks[i] != NULL)
	{
		if (toks[i][0] == '\0')
			cat = getcwd(cat, 0);
		else
			cat = dup_s(toks[i]);
		cat = st_cat(cat, "/");
		cat = st_cat(cat, str);
		if (access(cat, F_OK) == 0)
		{
			fr_dbptr(toks);
			return (cat);
		}
		free(cat);
		i++;
	}
	fr_dbptr(toks);
	return (str);
}

