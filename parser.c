#include "shell.h"

/**
 * parser - a function that selects function to execute a command..
 * @command: the command to be executed.
 *
 * Description: This is a function that calls upon a function which
 * returns an int.
 * Return: a function (if found) or NULL.
 */
int (*parser(char *command))(list * info)
{
	Builtins cmd[] = {
	{"cd", _cd},
	{"env", _env},
	{"exit", _exit_},
/*	{"alias", _alias},*/
	{"setenv", _mysetenv},
	{"unsetenv", _myunsetenv}
	};
	unsigned int i;

	for (i = 0; i < (sizeof(cmd) / sizeof(cmd[0])); ++i)
		if (_strcmp(cmd[i].name, command) == 0)
			return (cmd[i].func);

	return (NULL);
}
