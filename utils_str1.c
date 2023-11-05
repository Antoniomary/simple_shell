#include "shell.h"

/**
 * _strlen - a function that gets the length of a string.
 * @s: the string to get length of.
 *
 * Return: length of s.
 */
int _strlen(const char *s)
{
	const char *p;

	if (!s)
		return (0);

	for (p = s; *p; ++p)
		;

	return (p - s);
}

/**
 * _strcpy - a function that makes copy of a string.
 * @dest: where to copy from.
 * @src: where to copy to.
 *
 * Return: address to the newly copied string.
 */
char *_strcpy(char *dest, char *src)
{
	char *str = dest;

	if (!dest || !src)
		return (NULL);

	while ((*dest = *src) != '\0')
		++dest, ++src;

	return (str);
}

/**
 * _strncpy - a function that copies part of a string.
 * @dest: where to copy from.
 * @src: where to copy to.
 * @n: number of characters to copy.
 *
 * Return: address to the newly copied string.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i;

	if (!dest || !src)
		return (NULL);

	for (i = 0; src[i] && i < n; ++i)
		dest[i] = src[i];

	return (dest);
}

/**
 * _strcmp - a function that compares two strings.
 * @s1: the first string.
 * @s2: the second string.
 *
 * Return: 0 if s1 and s2 are equal; greater than 0 if s1 is greater or
 * less than 0 if s2 is greater.
 */
int _strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (0);

	for ( ; *s1 || *s2; ++s1, ++s2)
		if (*s1 != *s2)
			return (*s1 - *s2);

	return (*s1 - *s2);
}

/**
 * _strncmp - a function that compares a part of two strings.
 * @s1: the first string.
 * @s2: the second string.
 * @n: the number of characters to compare.
 *
 * Return: 0 if s1 and s2 are equal; greater than 0 if s1 is greater or
 * less than 0 if s2 is greater.
 */
int _strncmp(const char *s1, const char *s2, int n)
{
	int i;

	if (!s1 || !s2 || !n)
		return (0);

	for (i = 0; (s1[i] || s2[i]) && i < n; ++i)
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);

	return (0);
}
