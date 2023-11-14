#include "shell.h"

/**
 * _env - a function that prints the current environment variables.
 * @info: a struct tnat contains necessary information.
 *
 * Return: 0 (success) else 1 (failure).
 */
int _env(list *info)
{
	int i;
	char **environ = info->env;

	if (info->argv[1] == NULL)
	{
		for (i = 0; environ[i]; ++i)
			_puts(environ[i], 1);

		info->exit_status = 0;
	}
	else
	{
		if (!(isfile(info, info->argv[1]) & NONFILE))
			eputs("env: '", info->argv[1], "': No such file or directory", 1);

		info->exit_status = 1;
	}

	return (info->exit_status);
}

/**
 * _exit_ - a function that terminates a custom shell program.
 * @info: a struct tnat contains necessary information.
 *
 * Return: 0 (success) else 2 (failure).
 */
int _exit_(list *info)
{
	int status = 0; /* success code */
	char *msg = "exit: Illegal number: ";

	if (info->argv[1]) /* an exit code defined by user */
	{
		status = get_exit_status(info->argv[1]);

		if (status == -1) /* invalid or negative number */
		{
			_perror(SH_NAME, info->nth_line, msg, info->argv[1], "\n", NULL);
			info->exit_status = 2;
		}
		else /* status is a valid positive number */
		{
			info->exit = true;
			info->exit_status = status;
		}
	}
	else
		info->exit = true;

	return (info->exit_status);
}

/**
 * _mysetenv - a function that handles the setting of an environment variable.
 * @info: a struct tnat contains necessary information.
 *
 * Return: 0 (success) else 1 (failure).
 */
int _mysetenv(list *info)
{
	int i, c;
	char *err1 = "setenv: Too many arguments\n";
	char *err2 = "setenv: Too few arguments\n";
	char *err3 = ": Bad variable name\n";

	if (info->argc > 3)
		_perror(SH_NAME, info->nth_line, err1, NULL, NULL, NULL);
	else if (info->argc < 3)
		_perror(SH_NAME, info->nth_line, err2, NULL, NULL, NULL);
	else /* info->argv == 3 */
	{
		for (i = 0; info->argv[1][i]; ++i)
		{
			c = info->argv[1][i];
			if ((!i && !_isallowed(c)) || (!_isallowed(c) && !_isdigit(c)))
			{
				_perror(SH_NAME, info->nth_line, "setenv: ", info->argv[1], err3, NULL);
				info->exit_status = 1;
				return (1);
			}
		}

		i = _setenv(info, info->argv[1], info->argv[2], 1);
		info->exit_status = (i == 0) ? 0 : 1;
		return (i);
	}

	info->exit_status = 1;

	return (1);
}

/**
 * _myunsetenv - a function that handles removal of an environment variable.
 * @info: a struct tnat contains necessary information.
 *
 * Return: 0 (success) else 1 (failure).
 */
int _myunsetenv(list *info)
{
	int i, c;
	char *err1 = "unsetenv: Too many arguments\n";
	char *err2 = "unsetenv: Too few arguments\n";
	char *err3 = ": Bad variable name\n";

	if (info->argc > 2)
		_perror(SH_NAME, info->nth_line, err1, NULL, NULL, NULL);
	else if (info->argc < 2)
		_perror(SH_NAME, info->nth_line, err2, NULL, NULL, NULL);
	else /* info->argv == 2 */
	{
		for (i = 0; info->argv[1][i]; ++i)
		{
			c = info->argv[1][i];
			if ((!i && !_isallowed(c)) || (!_isallowed(c) && !_isdigit(c)))
			{
				_perror(SH_NAME, info->nth_line, "setenv: ", info->argv[1], err3, NULL);
				info->exit_status = 1;
				return (1);
			}
		}

		i = _unsetenv(info, info->argv[1]);
		info->exit_status = i == 0 ? 0 : 1;
		return (i);
	}

	info->exit_status = 1;

	return (1);
}

/**
 * _cd - a function that changes directory.
 * @info: a struct tnat contains necessary information.
 *
 * Return: 0 (success) else 1 (failure).
 */
int _cd(list *info)
{
	int ret;
	char *ptr = NULL, *old = _getenv(info, "PWD"), cwd[256];
	char *env_err = "cd: can't set environment: ";

	info->exit_status = 0;
	if (info->argv[1])
	{
		if (_strcmp(info->argv[1], "-") == 0)
		{
			ret = chdir((ptr = _getenv(info, "OLDPWD")));
			if (ret != -1)
				_puts(ptr, 1);
		}
		else
		{
			ptr = _strcmp(info->argv[1], "~") ? info->argv[1] : _getenv(info, "HOME");
			ret = chdir(ptr);
		}
	}
	else
		ret = chdir((ptr = _getenv(info, "HOME")));

	if (ret == -1) /* cd was unsuccesful */
	{
		_perror(SH_NAME, info->nth_line, "cd: can't cd to ", ptr, "\n", NULL);
		info->exit_status = 1;
	}
	else /* success */
		if (getcwd(cwd, 256))
		{
			_setenv(info, "OLDPWD", old, 1);
			_setenv(info, "PWD", cwd, 1);
		}
		else
		{
			_perror(SH_NAME, info->nth_line, NULL, env_err, NULL, "");
			info->exit_status = 1;
		}

	return (info->exit_status);
}
