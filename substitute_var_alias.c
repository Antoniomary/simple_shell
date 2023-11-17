#include "shell.h"

/**
 * substitute_var_alias - a function that does variable substitution.
 * @info: a struct that contains necessary information.
 */
void substitute_var_alias(list *info)
{
	int i, j;
	char *value = NULL;

	i = 0;
	while (info->argv[i])
	{
		if (info->argv[i][0] == '$' && info->argv[i][1])
		{
			/* first check in the environment variables */
			value = _getenv(info, &info->argv[i][1]);
			if (value)
			{
				info->argv[i++] = value;
				continue;
			}

			/* if not in env variables, checks user defined variables */
			value = get_var(info->var_head, &info->argv[i][1]);
			if (value)
			{
				info->argv[i++] = value;
				continue;
			}

			/* if no such variable, it is removed since it is nothing */
			for (j = 0; info->argv[i + j]; ++j)
				info->argv[i + j] = info->argv[i + j + 1];
			--info->argc;
			if (info->argv[i] == NULL)
				break;
		}
		else if (i == 0)
		{
			value = get_alias(info->alias_head, info->argv[i]);
			if (value)
				info->argv[i] = value;
		}
		++i;
	}
}

/**
 * get_alias - a function that gets the value stored in an alias.
 * @head: the head node of a singly linked list.
 * @str: the name to whose value is to be retrieved.
 *
 * Return: the value stored in the alias or NULL.
 */
char *get_alias(alias_t *head, char *str)
{
	while (head)
	{
		if (_strcmp(head->name, str) == 0)
			return (head->val);

		head = head->next;
	}

	return (NULL);
}

/**
 * get_var - a function that gets the value stored in a variable.
 * @head: the head node of a singly linked list.
 * @str: the name to whose value is to be retrieved.
 *
 * Return: the value stored in the alias or NULL.
 */
char *get_var(var_t *head, char *str)
{
	while (head)
	{
		if (_strcmp(head->name, str) == 0)
			return (head->val);

		head = head->next;
	}

	return (NULL);
}
