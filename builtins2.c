#include "shell.h"

/**
 * _alias - a function that handles aliasing.
 * @info: a struct tnat contains necessary information.
 *
 * Return: 0 (success) else 1 (failure).
 */
int _alias(list *info)
{
	int i;
	alias_t *new = NULL;
	char *err = ": memory allocation failure\n";

	if (!info->argv[1])
		info->exit_status = print_alias(info->alias_head);
	else
		for (i = 1; info->argv[i]; ++i)
		{
			if (_strchr(info->argv[i], '='))
			{
				new = NULL;
				new = creat_alias(info->argv[i]);
				if (!new)
				{
					eputs("Alias: can't set ", info->argv[i], err, 0);
					info->exit_status = 1;
				}
				else
					info->exit_status = add_replace_alias(&info->alias_head, new);
			}
			else
				info->exit_status = find_print_alias(info->alias_head, info->argv[i]);
		}

	return (0);
}
