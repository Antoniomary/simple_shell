#include "shell.h"

/**
 * custom_atoi - a function that convert a string of numbers to int.
 * @num: the string of numbers.
 *
 * Return: converted number.
 */
int custom_atoi(char *num)
{
	int i, n;

	for (i = n =  0; num[i]; ++i)
		n = 10 * n + (num[i] - '0');

	return (n);
}
