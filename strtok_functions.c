#include "shell.h"

/**
 * _strtok - a function that breaks a line of text into segments.
 * @str: the line of text to breakdown.
 * @delim: an array of characters where str would be broken.
 *
 * Return: a piece of str else NULL.
 */
char *_strtok(char *str, const char *delim)
{
	static char *ptr;
	char *token = NULL;

	/* checks str is the same arg as before */
	if (str == NULL && ptr == NULL) /* end of str has been reached */
		return (NULL);
	else if (str == NULL) /* yet to reach end */
		str = ptr;

	/* checks char one at a time a non delim char */
	while (*str && _strchr(delim, *str))
		++str;

	/* executes if str does not contain any delim char */
	if (*str == '\0')
		return (NULL);

	token = str; /* holds the start of str thst isn't a delim */
	/* search for the end where a delim is */
	while (*str && _strchr(delim, *str) == NULL)
		++str;

	if (*str != '\0') /* end with delim found */
	{
		*str = '\0'; /* repalce with null byte */
		ptr = str + 1; /* pointer to hold address for a comeback */
	}
	else /* the end of str has been reach i.e '\0' */
		ptr = NULL;

	return (token);
}

/**
 * _strtok_o_quote - a function that breaks a line of text into segments.
 * @s: the line of text to breakdown.
 * @delim: an array of characters where s would be broken.
 *
 * Description: when it breaks down the line of text, it ignores the
 * text enclosed in quotation marks.
 *
 * Return: a piece of s else NULL.
 */
char *_strtok_o_quote(char *s, const char *delim)
{
	static char *last_token;
	char *ptr = NULL, *token = NULL;

	if (!s && !last_token)
		return (NULL);
	else if (s == NULL)
		s = last_token;

	while (*s && _strchr(delim, *s))
		++s;
	if (*s == '\0')
		return (NULL);

	token = s;
	while (*s && (_strchr(delim, *s) == NULL))
	{
		if (*s == '\'' || *s == '"')
		{
			ptr = ignore_quotes(s, *s);
			if (ptr)
				s = ptr;
			continue;
		}
		++s;
	}

	if (*s != '\0')
	{
		*s = '\0';
		last_token = s + 1;
	}
	else
		last_token = NULL;

	return (token);
}

/**
 * strcmd_and_sep - a function that breaks a line of text into segments.
 * and saves the delim if it is & or | else NUL.
 * @s: the line of text to breakdown.
 * @delim: an array of characters where s would be broken.
 * @sep: where to save the the delim.
 * @saveptr: records the address to continue breaking down text.
 *
 * Return: a piece of str else NULL.
 */
char *strcmd_and_sep(char *s, const char *delim, char *sep, char **saveptr)
{
	static char *last_token;
	char *ptr = NULL, *token = NULL;

	if (!s && !last_token)
		return (NULL);
	else if (s == NULL)
		s = last_token;

	while (*s && _strchr(delim, *s))
		++s;
	if (*s == '\0')
		return (NULL);

	token = s;
	while (*s && (_strchr(delim, *s) == NULL))
	{
		if (*s == '\'' || *s == '"')
		{
			ptr = ignore_quotes(s, *s);
			if (ptr)
				s = ptr;
			continue;
		}
		++s;
	}
	*sep = (*s == '&') ? AND : (*s == '|') ? OR : NUL;

	if (*s != '\0')
	{
		*s = '\0';
		last_token = s + 1;
	}
	else
		last_token = NULL;

	if (saveptr)
		*saveptr = last_token;

	return (token);
}

/**
 * dequote - a function that removes quotation marks from a set of characters.
 * @entry: a double pointer to the set of characters.
 */
void dequote(char **entry)
{
	int a, b, i, len;
	char c;

	for (i = 0; entry[i]; ++i)
	{
		len = _strlen(entry[i]);
		c = entry[i][0];
		if ((c == '\'' || c == '"') && (entry[i][len - 1] == c) && (len - 1) != 0)
		{
			entry[i][len - 1] = '\0';
			entry[i] = &entry[i][1];
		}
		else if (len > 1)
		{
			for (a = b = 0; entry[i][a]; ++a)
			{
				c = entry[i][a];
				if (c != '\'' && c != '"')
					entry[i][b++] = c;
			}
			entry[i][b] = '\0';
		}
	}
}
