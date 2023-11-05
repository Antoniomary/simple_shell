#include "shell.h"

/**
 * _which - a function that searchs the PATH directories for a command.
 * @info: a struct tnat contains necessary information.
 * @cmd: the command to search for.
 *
 * Return: The path of cmd if found else NULL.
 */
char *_which(list *info, char *cmd)
{
	char *dir = NULL, *path = NULL, *value = NULL;
	struct stat st;

	value = _getenv(info, "PATH"); /* get the variable */
	if (!value) /* not found in enviroment variables */
		return (NULL);

	value = _strdup(value); /* makes duplicate */
	if (!value) /* malloc failure */
		return (NULL);

	/* gets each directory in path variable */
	dir = _strtok(value, ":");
	while (dir)
	{
		/* form path to test if cmd exist */
		path = str_concat(dir, cmd, '/');

		if (stat(path, &st) == 0) /* tests for cmd */
		{
			free(value);
			return (path); /* cmd found */
		}

		free(path); /* not found yet hence free space */
		dir = _strtok(NULL, ":"); /* get next directory */
	}

	free(value);

	return (NULL); /* means not found */
}
