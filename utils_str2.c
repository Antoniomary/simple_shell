#include "shell.h"

/**
 * _strdup - a function dynamically allocates space and duplicates a stting.
 * @s: thr string to duplicate.
 *
 * Return: pointer to the new string or NULL (failure).
 */
char *_strdup(char *s)
{
	int len;
	char *new = NULL;

	if (s)
	{
		for (len = 0; s[len]; ++len)
			;

		new = malloc(sizeof(char) * (len + 1));
		if (new)
			_strcpy(new, s);
	}

	return (new);
}

/**
 * str_concat - a function that concatenate strings to produce a new string.
 * @s1: first string.
 * @s2: second string.
 * @c: character to place in between s1 and s2.
 *
 * Return: pointer to a new string or NULL (failure).
 */
char *str_concat(const char *s1, const char *s2, char c)
{
	int i, j;
	int len1 = _strlen(s1);
	int len2 = _strlen(s2);
	char *new_str = alloc(len1 + len2 + 2);

	if (new_str)
	{
		for (i = 0; i < len1; ++i)
			new_str[i] = s1[i];

		new_str[i++] = c;

		for (j = 0; j < len2; ++j)
			new_str[i + j] = s2[j];

		new_str[i + j] = '\0';
	}

	return (new_str);
}

/**
 * _strchr - a function that finds a character in a string.
 * @s: the string.
 * @c: the character to find in s.
 *
 * Return: the address of the character if found, else NULL
 */
char *_strchr(const char *s, int c)
{
	if (s)
		for ( ; *s; ++s)
			if (*s == c)
				return ((char *) s);

	return (NULL);
}

/**
 * _strcat - a function that concatenate strings to produce a new string.
 * @str: string to receive other strings..
 * @s1: first string.
 * @s2: second string.
 * @s3: third string.
 * @s4: fourth string.
 *
 * Return: pointer to a new string or NULL (failure).
 */
char *_strcat(char *str, char *s1, char *s2, char *s3, char *s4)
{
	int i, len;

	len = _strlen(str);
	if (s1)
		for (i = 0; s1[i]; ++i)
			str[len++] = s1[i];

	if (s2)
		for (i = 0; s2[i]; ++i)
			str[len++] = s2[i];

	if (s3)
		for (i = 0; s3[i]; ++i)
			str[len++] = s3[i];

	if (s4)
		for (i = 0; s4[i]; ++i)
			str[len++] = s4[i];

	str[len] = '\0';

	return (str);
}

/**
 * str_dup_cat - a function that concatenate strings to produce a new string.
 * @s1: first string.
 * @s2: second string.
 * @s3: third string.
 * @s4: fourth string.
 *
 * Return: pointer to a new string or NULL (failure).
 */
char *str_dup_cat(char *s1, char *s2, char *s3, char *s4)
{
	int i, len;
	char *str = NULL;

	len = _strlen(s1) + _strlen(s2) + _strlen(s3) + _strlen(s4);
	str = alloc(len + 1);
	if (str)
	{
		len = 0;
		if (s1)
			for (i = 0; s1[i]; ++i)
				str[len++] = s1[i];

		if (s2)
			for (i = 0; s2[i]; ++i)
				str[len++] = s2[i];

		if (s3)
			for (i = 0; s3[i]; ++i)
				str[len++] = s3[i];

		if (s4)
			for (i = 0; s4[i]; ++i)
				str[len++] = s4[i];

		str[len] = '\0';
	}

	return (str);
}
