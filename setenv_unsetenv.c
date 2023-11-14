#include "shell.h"

/**
 * _setenv - a function that sets an environment variable.
 * @info: a struct that contains necessary information.
 * @name: the name to set the environment variable.
 * @value: the value to set the environment variable.
 * @overwrite: a flag that tells if to overwrite variable if it exists or not.
 *
 * Return: 0 (success), else 1 (failure).
 */
int _setenv(list *info, const char *name, const char *value, int overwrite)
{
	int i, len;
	char *ptr = _strchr(name, '=');

	if (!name || *name == '\0' || ptr)
	{
		errno = EINVAL, ptr = ptr ? info->argv[1] : "variable";
		_perror(SH_NAME, info->nth_line, "can't set ", ptr, ": ", "");
		return (1);
	}

	ptr = str_concat(name, value, '=');
	if (!ptr)
	{
		errno = ENOMEM;
		_perror(SH_NAME, info->nth_line, NULL, NULL, "can't set ", info->argv[1]);
		return (1);
	}

	len = _strlen(name);
	for (i = 0; info->env[i]; ++i)
		if (_strncmp(name, info->env[i], len) == 0)
			if (info->env[i][len] == '=')
			{
				if (overwrite)
				{
					free(info->env[i]);
					info->env[i] = ptr;
				}
				return (0);
			}

	if (realloc_env(info) == 0)
	{
		info->env[i++] = ptr;
		info->env[i] = NULL;
		return (0);
	}
	free(ptr);

	return (1);
}

/**
 * _unsetenv - a function that unsets an environment variable.
 * @info: a struct that contains necessary information.
 * @name: the name of the environment variable to unset.
 *
 * Return: 0 (success), else 1 (failure).
 */
int _unsetenv(list *info, const char *name)
{
	int i, len;
	char *ptr = NULL, **env = info->env;

	if (!name || *name == '\0' || _strchr(name, '='))
	{
		errno = EINVAL;
		ptr = ptr ? info->argv[1] : "variable";
		_perror(SH_NAME, info->nth_line, "can't set ", ptr, ": ", "");
		return (-1);
	}

	len = _strlen(name);
	for (i = 0; env[i]; ++i)
		if (_strncmp(name, env[i], len) == 0)
			if (env[i][len] == '=')
			{

				ptr = env[i];
				while ((env[i] = env[i + 1]) != NULL)
					++i;

				info->env_size--;
				free(ptr);

				return (0);
			}
	return (0);
}
