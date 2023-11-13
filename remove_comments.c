#include "shell.h"

/**
 * remove_comment - a function that removes comments from a line.
 * @line: the line to remove comment from.
 *
 * Return: non-zero integer if comment was removed, else 0.
 */
int remove_comment(char *line)
{
	int i = 0;

	if (line[i] != '#') /* 1st char is not a comment */
	{
		for (i = 1; line[i]; ++i)
		{
			if (line[i - 1] == ' ' && line[i] == '#') /* comment has been found */
				break;

			/* start of a quote, # are untouched */
			if (line[i] == '\'' || line[i] == '"')
			{
				++i;
				/* search for end of quote */
				while (line[i] && (line[i] != '\'' || line[i] != '"'))
					++i;

				if (line[i] == '\0')
					return (i);
			}

		}
	}

	line[i] = '\0';

	if (i == 0)
		free(line);

	return (i);
}
