#include "shell.h"

/**
 * syntax_error_check - a function that parses a text for syntax errors.
 * @info: pointer to a struct that holds necessary informations.
 * @line: string to parse.
 *
 * Return: a non-zero integer if error exits else 0 if not.
 */
int syntax_error_check(list *info, char *line)
{
	if (unclosed_quote(info, line) == true)
		return (ERROR);

	if (check_cmd_separators(info, line) == true)
		return (ERROR);

	return (NO_ERROR);
}

/**
 * unclosed_quote - a function that checks if quotation marks are closed.
 * @info: pointer to a struct that holds necessary informations.
 * @s: string to check.
 *
 * Return: true if is unclose quote is found, else false.
 */
int unclosed_quote(list *info, char *s)
{
	int found_quote = false;
	char *error = "Syntax error: Unterminated quoted string\n";

	while (*s)
	{
		if (*s == '\'' || *s == '"')
		{
			found_quote = *s++;
			while (*s)
			{
				if (*s == found_quote)
				{
					found_quote = false;
					break;
				}
				++s;
			}

			if (found_quote)
			{
				_perror(SH_NAME, info->nth_line, error, NULL, NULL, NULL);
				free(s);
				info->exit_status = 2;
				update_exitstatus_var(info);

				return (true);
			}
		}
		++s;
	}

	return (false);
}

/**
 * check_cmd_separators - a function that checks the syntax for command
 * separators (i.e. ;, &&, and ||) in a string.
 * @info: pointer to a struct that holds necessary informations.
 * @s: string to check.
 *
 * Return: YES if error occurred or NO if not.
 */
int check_cmd_separators(list *info, char *s)
{
	int c,  sep = NO, cmd = NO, one = NO, err_status = NO;

	while ((err_status == NO) && (c = *s) != '\0')
	{
		if (_isspace(c) && ++s)
			continue;
		else if (is_op(c))
		{
			c == ';' ? (sep = SEMI) : c == '|' ? (one = OR) : (one = AND);

			for (++s; (c = *s) && (is_op(c) || _isspace(c)); ++s)
				if (c == ';')
					break;
				else if (c == '|' || c == '&')
				{
					if (sep)
						break;

					sep = (c == '|') ? OR : AND;
					one = NO;
				}
		}
		else /* c is the 1st letter of a command */
			for (cmd = YES; (c = *s) && !is_op(c); ++s)
				if (c == '\'' || c == '"')
					s = ignore_quotes(s, c) - 1;

		if (check_error(info, s, &cmd, &sep, one, c) == true)
		{
			err_status = YES;
			info->exit_status = 2;
			free(s);
			update_exitstatus_var(info);
		}
	}

	return (err_status);
}

/**
 * check_error - a function that prints the appropiate error message.
 * @info: pointer to a struct that holds necessary informations.
 * @s: string to check for the exact error.
 * @cmd: a flag.
 * @sep: a flag.
 * @one: a flag.
 * @c: a variable to hold a character.
 *
 * Return: true if error was found or false if not.
 */
int check_error(list *info, char *s, int *cmd, int *sep, int one, int c)
{
	char *syn = "Syntax error: ", err[5];
	char *syn_eof = "Syntax error: end of file unexpected\n";

	if (*cmd && *sep)
	{
		if (is_op(c))
		{
			if (c == ';')
				_strcpy(err, *(s - 1) == c ? "\";;\"" : "\";\"");
			else if (c == '|')
				_strcpy(err, *(s + 1) == c ? "\"||\"" : "\"|\"");
			else /* c == '&' */
				_strcpy(err, *(s + 1) == c ? "\"&&\"" : "\"&\"");

			_perror(SH_NAME, info->nth_line, syn, err, " unexpected\n", NULL);
			return (true);
		}
		else if (c != '\0') /* another cmd is next */
			*cmd = *sep =  NO;
		else if (*sep != SEMI) /* only semi can come before '\0' */
		{
			_perror(SH_NAME, info->nth_line, syn_eof, NULL, NULL, NULL);
			return (true);
		}
	}
	else if (!(*cmd) || one)
	{
		if (*sep == AND || *sep == OR)
			_strcpy(err, *sep == OR ? "\"||\"" : "\"&&\"");
		else if (one)
			_strcpy(err, one == OR ? "\"|\"" : "\"&\"");
		else if (*sep == SEMI)
			_strcpy(err, *(s - 1) == c ? "\";;\"" : "\";\"");

		_perror(SH_NAME, info->nth_line, syn, err, " unexpected\n", NULL);
		return (true);
	}

	return (false);
}
