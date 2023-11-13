#include "shell.h"

/**
 * free_env - a function that frees all environment variables.
 * @info: a struct that contains necessary information.
 */
void free_env(list *info)
{
	int i;

	for (i = 0; i < info->env_size; ++i)
		free(info->env[i]);

	free(info->env);
}

/**
 * free_env_alias_vars - a function that calls on functions that free
 * environment, alias, and variables in a shell program.
 * @info: a struct that contains necessary information.
 */
void free_env_alias_vars(list *info)
{
	free_env(info);
	free_alias(info->alias_head);
	free_var(info->var_head);
}
