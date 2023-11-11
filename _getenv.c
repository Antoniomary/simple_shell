#include "shell.h"

/**
 * _getenv - a function that checks if a variable is present in the list of
 * environment variables.
 * @info: a struct tnat contains necessary information.
 * @name: the variable to check.
 *
 * Return: the address of the variable if present, else NULL.
 */
char *_getenv(list *info, const char *name)
{
	int i, len = _strlen(name);
	char **environ = info->env;

	for (i = 0; environ[i] != NULL; ++i)
		if (_strncmp(name, environ[i], len) == 0)
			if (environ[i][len] == '=')
				return (&environ[i][len + 1]);

	return (NULL);
}
