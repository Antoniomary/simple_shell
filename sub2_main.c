#include "shell.h"

/**
 * sig_hand - a function that handles a signal.
 * @signum: the signal to be handled
 */
void sig_hand(int signum)
{
	if (signum == SIGINT)
	{
		_putchar('\n');
		display_prompt();
	}
}

/**
 * is_all_var_def - a function that checks if a user input is all variable
 * definition or not.
 * @info: a struct that contains necessary information.
 *
 * Return: 0 if yes else a non-zero integer if not
 */
int is_all_var_def(list *info)
{
	int i, j, flag = true, used_quote = false;
	char *err = "Syntax error: Unterminated quoted string";

	for (i = 0; flag && info->argv[i]; ++i)
		if (_strchr(info->argv[i], '=')) /* possible variable definition */
		{
		if (!_isdigit(info->argv[i][0])) /* checks that 1st char is not a number */
		{
			/* checks the name part of the variable definition */
			for (j = 1; _isallowed(info->argv[i][j]); ++j)
				;
			if (info->argv[i][j] == '=') /* reached end of name part */
			{	/**
				 * moves j to the 1st char of value, however
				 * if user used quote, it stores it and moves j over the mark
				 */
				if (++j && (info->argv[i][j] == '\'' || info->argv[i][j] == '"'))
					used_quote = info->argv[i][j++];

				/* go to end of value part */
				for ( ; info->argv[i][j]; ++j)
					/* accounts for closing and matching pair of quote marks */
					if (used_quote && (info->argv[i][j] == used_quote))
						used_quote = false;

				if (used_quote)
				{
					_perror(SH_NAME, info->nth_line, err, NULL, NULL, NULL);
					flag = false;
				}

			}
			else
				flag = false;
		}
		}
		else /* definitely not a variable definition: a command */
			flag = false;

	return (flag ? true : false);
}

/**
 * define_user_var - a function that defines a user's variable.
 * @info: a struct that contains necessary information.
 */
void define_user_var(list *info)
{
	int i;
	var_t *new = NULL;
	char *msg = "can't add user-defined variable: ";

	info->exit_status = 0;

	for (i = 0; info->argv[i]; ++i)
	{
		new = creat_var(info->argv[i]);
		if (new)
			add_replace_var(&info->var_head, new);
		else
		{
			_perror(SH_NAME, info->nth_line, msg, info->argv[i], ": ", "");
			info->exit_status = 1;
			break;
		}
	}
}

/**
 * sort_var_from_cmd - a function that sorts a line of text for variable
 * definitions.
 * @info: a struct that contains necessary information.
 */
void sort_var_from_cmd(list *info)
{
	int i, j;

	for (i = 0; info->argv[i]; ++i) /* find 1st command */
		if (_strchr(info->argv[i], '=') == NULL)
			break;

	if (i > 0) /* at least one var def was entered by user */
	{
		/* remove the var def before the 1st command */
		for (j = 0; info->argv[i]; ++j, ++i)
			info->argv[j] = info->argv[i];

		info->argv[j] = NULL;

		info->argc = j; /* update argc to the current argv */
	}
}
