#include "shell.h"

/**
 * _putchar - a function that prints a single character to stdout.
 * @c: the character to print.
 *
 * Return: the character printed (success), else -1.
 */
int _putchar(int c)
{
	fflush(stdout);

	return (write(STDOUT_FILENO, &c, 1));
}

/**
 * eputchar - a function that prints a single character to stderr.
 * @c: the character to print.
 *
 * Return: the character printed (success), else -1.
 */
int eputchar(int c)
{
	fflush(stderr);

	return (write(STDERR_FILENO, &c, 1));
}

/**
 * _puts - a function that prints a string to stderr.
 * it has an option to print a newline or not.
 * @s: the string to print.
 * @newline: the flag for newline.
 */
void _puts(const char *s, int newline)
{
	int len = _strlen(s);

	fflush(stdout);
	write(STDOUT_FILENO, s, len);

	if (newline)
		_putchar('\n');
}

/**
 * eputs - a function that prints a string(s) to stderr.
 * it has an option to print a newline or not.
 * @s1: the string to print, first segment.
 * @s2: the string to print, second segment.
 * @s3: the string to print, third segment.
 * @newline: the flag for newline.
 */
void eputs(const char *s1, const char *s2, const char *s3, int newline)
{
	fflush(stdout);

	if (s1)
		write(STDERR_FILENO, s1, _strlen(s1));
	if (s2)
		write(STDERR_FILENO, s2, _strlen(s2));
	if (s3)
		write(STDERR_FILENO, s3, _strlen(s3));

	if (newline)
		_putchar('\n');
}

/**
 * _perror - a function that prints a string(s) in segments to stderr.
 * @s:the string to print (segment).
 * @n: a number.
 * @s2: the string to print (segment).
 * @s1: the string to print (segment).
 * @s2: the string to print, (segment).
 * @s3: the string to print, (segment).
 * @s4: the string to print, (segment).
 */
void _perror(char *s, unsigned int n, char *s1, char *s2, char *s3, char *s4)
{
	int i = 0, len;
	char t_buf[16], buf[128]; /* buffers to process output */

	if (!s) /* s is NULL */
	{
		perror(s4);
		return;
	}

	/* copy program name first */
	for (len = 0; s[len] ; ++len)
		buf[len] = s[len];
	buf[len++] = ':';
	buf[len++] = ' ';
	/* gets each digit of n into t_buf */
	do {
		t_buf[i++] = n % 10u + '0';
	} while ((n /= 10u) != 0);
	/* read n to buf */
	for (--i; i >= 0; --i, ++len)
		buf[len] = t_buf[i];
	buf[len++] = ':';
	buf[len++] = ' ';

	write(STDERR_FILENO, buf, len);

	if (s1)
		write(STDERR_FILENO, s1, _strlen(s1));
	if (s2)
		write(STDERR_FILENO, s2, _strlen(s2));
	if (s3)
		write(STDERR_FILENO, s3, _strlen(s3));
	if (s4)
	{
		perror(s4);
		fflush(stderr);
	}
}
