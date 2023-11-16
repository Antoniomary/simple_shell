#include "shell.h"

/**
 * display_prompt - a function that prints a prompt to stdout.
 */
void display_prompt(void)
{
	char *prompt = "#cisfun$ ";
	char *prompt_colour = "\x1b[32m"; /* green */
	char *normal_colour = "\x1b[0m"; /* default */

	_puts(prompt_colour, 0);
	_puts(prompt, 0);
	_puts(normal_colour, 0);
}

/**
 * read_line - a function that gets input from user.
 * @info: a struct that contains necessary information.
 *
 * Return: the input of user.
 */
char *read_line(list *info)
{
	char *line = NULL;
	size_t n = 0;
	ssize_t bytes_read = _getline(&line, &n, info->fd);

	if (bytes_read > 0)
	{
		if (line[bytes_read - 1] == '\n')
		{
			line[bytes_read - 1] = '\0';
			info->nth_line++;
		}

		return (line);
	}

	if (bytes_read == 0 && info->sh_mode == INT_MODE) /*  CTRL + D detected */
	{
		if (*line)
			return (line);

		_putchar('\n'); /* means exit shell */
	}
	/* means (1) error reading line or (2) memory related problem */
	else if (bytes_read == -1)
		_perror(SH_NAME, info->nth_line, NULL, NULL, NULL, "getline");

	free(line);
	free_env_alias_vars(info);

	if (info->fd != STDIN_FILENO)
		if (close(info->fd) == -1)
			_perror(SH_NAME, info->nth_line, NULL, NULL, "cannot close ", FILENAME);

	exit(info->exit_status);
}

/**
 * token_input - a function that tokenizes a line of text.
 * @info: a struct that contains necessary information.
 * @str: the line of text.
 *
 * Return: an argument vector of the tokens (success) else NULL (failure).
 */
char **token_input(list *info,  char *str)
{
	int i, words = 0;
	char *token = NULL, **argv = NULL, *str_copy = NULL;

	info->argc = 0;
	str_copy = _strdup(str);
	if (!str_copy)
		return (NULL);

	token =  _strtok_o_quote(str_copy, " \t&|");
	while (token)
	{
		++words;
		token = _strtok_o_quote(NULL, " \t&|");
	}
	free(str_copy);

	argv = malloc(sizeof(char *) * (words + 1));
	if (!argv)
		return (NULL);

	info->argc = words;
	token = _strtok_o_quote(str, " \t");
	for (i = 0; token; ++i)
	{
		argv[i] = token;
		token = _strtok_o_quote(NULL, " \t");
	}
	argv[i] = NULL; /* end vector with null */

	return (argv);
}

/**
 * find_path - a function that handles the whether to check for a command path
 * or not.
 * @info: a struct that contains necessary information.
 * @path: a double pointer to the paths to be checked.
 * @command: the command to be searched for in the path.
 */
void find_path(list *info, char **path, char *command)
{
	/* checks if command was input with its own path */
	if (_strchr(command, '/'))
		*path = _strdup(command);

	else
	/**
	 * If command is found, path will hold the directory
	 * it can be found.
	 * If command is not found, path will be null
	 */
		*path = _which(info, command);
}

/**
 * execute_cmd - a function that executes a command.
 * @info: a struct that contains necessary information.
 *
 * Return: 0 (sucess) else a non-zero integer (failure).
 */
int execute_cmd(list *info)
{
	pid_t pid;
	char *cmd_path = NULL;
	int status, (*builtin)(list *info);

	builtin = parser(info->argv[0]);
	if (builtin) /* command is a built-in function */
	{
		builtin(info);
		_setenv(info, "_", info->argv[0], 1);
		return (0);
	}

	find_path(info, &cmd_path, info->argv[0]);
	if (cmd_path) /* cmd exists in path as a normal program */
	{
		pid = fork();
		if (pid < 0) /* fork the process: -1 means failure*/
		{
			_perror(NULL, 0, NULL, NULL, NULL, "fork");
			return ((info->exit = true));
		}
		else if (pid == 0) /* success: create child */
		{
			execve(cmd_path, info->argv, info->env);
			_perror(NULL, 0, NULL, NULL, NULL, "execve");
			exit(EXIT_FAILURE);
		}
		/* parent process waits for child */
		wait(&status);
		info->exit_status = WEXITSTATUS(status);
		free(cmd_path);
		_setenv(info, "_", info->argv[0], 1);
	}
	else /* cmd not found */
	{
		_perror(SH_NAME, info->nth_line, info->argv[0], ": not found\n", NULL, NULL);
		info->exit_status = 127;
	}

	return (0);
}
