#include "shell.h"

/**
 * _isdigit - a function that checks if a character is a digit.
 * @c: the character to check.
 *
 * Return: true (success) else false (failure).
 */
int _isdigit(int c)
{
	return ((c >= '0' && c <= '9') ? true : false);
}

/**
 * _isalpha - a function that checks if a character is an alphabet..
 * @c: the character to check.
 *
 * Return: true (success) else false (failure).
 */
int _isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ? true : false);
}

/**
 * _isallowed - a function that checks if a character is part of a set of
 * allowed characters.
 * @c: the character to check.
 *
 * Return: the exact operator that it is.
 */
int _isallowed(int c)
{
	if ((c == '_') ||
		(c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z') ||
		(c >= '0' && c <= '9'))
		return (true);

	return (false);
}

/**
 * is_op - a function that checks if a character is an operator
 * ;, |, or &..
 * @c: the character to check.
 *
 * Return: the exact operator that it is.
 */
int is_op(int c)
{
	return ((c == ';' || c == '&' || c == '|'));
}

/**
 * _isspace - a function that checks if a character is a white space.
 * @c: the character to check.
 *
 * Return: the exact operator that it is.
 */
int _isspace(int c)
{
	return (c == ' ' || c == '\t');
}
