#include "shell.h"

/**
 * isfile - a function that checks if a file exists as a file or not
 * @info: a struct that contains necessary information.
 * @filename: the name of the file to be checked.
 *
 * Return: a non-zero integer (success)
 */
int isfile(list *info, char *filename)
{
	int status = 0; /* assumes filename does not exist */
	struct stat st;

	(void) info;

	if (stat(filename, &st) == 0)
	{
		if (S_ISREG(st.st_mode))
			status |= ISFILE;
		else /* exist as something else */
			status |= NONFILE;
	}
	else
	{
		_perror(SH_NAME, 0, "cannot access ", filename, ": ", "stat");
		return (1); /* TODO: watch out ... */
	}

	return (status);
}

/**
 * get_exit_status - a function that gets exit code given with exit command.
 * @s: the exit code in a character array.
 *
 * Return: a non-zero integer (success)
 */
int get_exit_status(const char *s)
{
	int i = 0; /* indexing variable */
	int n = -1; /* holds the status number */

	if (_isdigit(s[i]))
	{
		for (n = 0; s[i] && _isdigit(s[i]); ++i)
		{
			n = n * 10 + (s[i] - '0');
			n %= 256; /* keeps n within range of exit status that mean something */
		}

		if (s[i] != '\0')
			n = -1;
	}

	return (n);
}

/**
 * _itoa - a function that converts an integer to ascii.
 * @n: the integer.
 * @num: where to store the ascii.
 *
 * Return: a non-zero integer (success)
 */
char *_itoa(int n, char *num)
{
	int i, len;
	char temp[15];

	/* gets each digit of n into temp n reverse */
	len = 0;
	do {
		temp[len++] = n % 10 + '0';
	} while ((n /= 10) != 0);

	/* read n from temp to num */
	i = 0;
	for (--len; len >= 0; --len, ++i)
		num[i] = temp[len];
	num[i] = '\0';

	return (num);
}

/**
 * space_skipper - a function that skips over spaces.
 * @entry: the string where the spaces occur.
 *
 * Return: a non-zero integer (success)
 */
char *space_skipper(char *entry)
{
	int i;

	for (i = 0; _isspace(entry[i]); ++i)
		;

	return (&entry[i]);
}

/**
 * ignore_quotes - a function that helps another function
 * ignore text in quotation marks in a string.
 * @s: the string.
 * @c: the type of quote mark to signal the end of the quote.
 *
 * Return: a non-zero integer (success)
 */
char *ignore_quotes(char *s, int c)
{
	char *temp = s;

	if (!s)
		return (NULL);

	for (++s; *s; ++s)
		if (*s == c)
			return (++s);

	return (++temp);
}
