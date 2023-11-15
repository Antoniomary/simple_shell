#include "shell.h"

/**
 * sh_start_up - a function that sets up start-up activities for a program.
 * @info: a struct that contains necessary information.
 * @av: argument vector at command line.
 */
void sh_start_up(list *info, char **av)
{
	info->av = av;
	shell_init(info);
	env_init(info);
	if (var_init(info) == 1)
	{
		eputs(info->av[0], ": cannot set up variables for substitution: ", NULL, 1);
		free_env(info);
		free_var(info->var_head);
		exit(1);
	}
}

/**
 * shell_init - a function that sets the mode that shell would run in and
 * also where to get input from.
 * @info: a struct that contains necessary information.
 */
void shell_init(list *info)
{
	int status;

	if (isatty(STDIN_FILENO) && !FILENAME) /* from terminal */
	{
		info->fd = STDIN_FILENO;
		info->sh_mode = INT_MODE;
		return;
	}

	if (FILENAME) /* input from file */
	{
		status = isfile(info, FILENAME);

		if (status & ISFILE)
		{
			info->fd = open(FILENAME, O_RDONLY);
			if (info->fd == -1)
			{
				_perror(SH_NAME, 0, NULL, "cannot open ", NULL, FILENAME);
				exit(2);
			}
		}
		else if (status & NONFILE)
			exit(EXIT_SUCCESS);
		else
		{
			_perror(SH_NAME, 0, "cannot open ", FILENAME, ": No such file\n", NULL);
			exit(2);
		}
	}
	else /* input from another program */
		info->fd = STDIN_FILENO;

	info->sh_mode = NON_INT_MODE;
}

/**
 * env_init - a function that creates environment variables.
 * @info: a struct that contains necessary information.
 */
void env_init(list *info)
{
	int i, shlvl;
	char value[10];

	/* count variables in environment */
	for (i = 0; environ[i]; ++i)
		++info->env_size;

	/* dynamically allocate space for variables */
	info->env = (char **) malloc(sizeof(char *) * (info->env_size + 1));
	if (!info->env)
	{
		eputs(info->av[0], ": cannot initialize environment: ", NULL, 0);
		perror("");
		exit(1);
	}

	/* make duplicate of environment variables */
	for (i = 0; i < info->env_size; ++i)
	{
		info->env[i] = _strdup(environ[i]);
		if (!info->env[i])
		{
			eputs(info->av[0], ": cannot initialize environment: ", NULL, 0);
			perror("");
			info->env_size = i;
			free_env(info);
			exit(1);
		}
	}
	info->env[i] = NULL; /* terminate list */

	shlvl = custom_atoi(_getenv(info, "SHLVL"));
	_itoa(++shlvl, value);
	if (_setenv(info, "SHLVL", value, 1))
	{
		free_env(info);
		exit(1);
	}
}

/**
 * var_init - a function that creates variables for substitution.
 * @info: a struct that contains necessary information.
 *
 * Return: 0 (success), else 1 (failure).
 */
int var_init(list *info)
{
	pid_t sh_pid = getpid();
	char num[15];
	var_t *new = malloc(sizeof(var_t));

	if (!new)
		return (1);

	new->name = _strdup("?");
	if (!new->name)
		return (free(new), 1);

	new->val = _strdup("0");
	if (!new->val)
		return (free(new->name), free(new), 1);

	new->next = NULL;
	add_replace_var(&info->var_head, new);

	new = malloc(sizeof(var_t));
	if (!new)
		return (1);

	_itoa(sh_pid, num);
	new->name = _strdup("$");
	if (!new->name)
		return (free(new), 1);

	new->val = _strdup(num);
	if (!new->val)
		return (free(new->name), free(new), 1);

	new->next = NULL;
	add_replace_var(&info->var_head, new);

	return (0);
}
