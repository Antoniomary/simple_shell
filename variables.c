#include "shell.h"

/**
 * creat_var - a function that creates a variable.
 * @entry: the alias to be created in the form of name=value
 *
 * Return: the address of the newly created variable else NULL.
 */
var_t *creat_var(char *entry)
{
	int i = 0, used_quote = false;
	char *ptr = NULL;
	var_t *new = malloc(sizeof(var_t));

	if (new)
	{
		/* get name part */
		ptr = _strtok(entry, "=");
		new->name = _strdup(ptr); /* make duplicate of it */
		if (!new)
			return (free(new), NULL);
		/* get value part */
		ptr = _strtok(NULL, "\0");
		new->val = alloc(_strlen(ptr) + 1); /* allocate space */
		if (!new->val)
			return (free(new->name), free(new), NULL);
		if (ptr && *ptr) /* user may have value equal to nothing */
		{
			ptr = space_skipper(ptr);
			for ( ; *ptr; ++ptr)
			{
				/* skip quote mark if any */
				if (*ptr == '\'' || *ptr == '"')
					used_quote = *ptr++;
				/* match closing quote */
				if (used_quote && (*ptr == used_quote))
				{
					used_quote = false;
					continue;
				}
				new->val[i++] = *ptr;
				ptr = _isspace(*ptr) ? (space_skipper(ptr) - 1) : ptr;
			}
			i = (i > 0 && _isspace(new->val[i - 1])) ? i - 1 : i;
		}
		new->val[i] = '\0', new->next = NULL;
	}

	return (new);
}

/**
 * add_replace_var - a function that adds or replaces a new or existing
 * variable respectively.
 * @head: pointer to head node.
 * @new: new or modified variable to be added or replaced.
 */
void add_replace_var(var_t **head, var_t *new)
{
	var_t *temp = *head;

	if (!(*head))
		*head = new;
	else
	{
		while (temp)
		{
			if (_strcmp(temp->name, new->name) == 0)
			{
				free(temp->val);
				temp->val = new->val;
				free(new->name);
				free(new);

				return;
			}

			if (!temp->next)
				break;

			temp = temp->next;
		}

		temp->next = new;
	}
}

/**
 * free_var - a function that frees a singly linked list.
 * @head: pointer to the head node of the list to free.
 */
void free_var(var_t *head)
{
	if (head)
	{
		var_t *temp = head;

		while (head)
		{
			temp = head;
			head = head->next;
			free(temp->name);
			free(temp->val);
			free(temp);
		}
	}
}

/**
 * update_exitstatus_var - a function that updates the last exit code variable
 * @info: a struct that contains necessary information.
 */
void update_exitstatus_var(list *info)
{
	static int i;
	static char *num;

	if (i == 0)
	{
		num = alloc(15);
		if (!num)
		{
			eputs(SH_NAME, ": memory allocation failure: Out of memory\n", NULL, 0);
			info->exit = true;
		}
		free(info->var_head->val);
		i = 1;
	}

	_itoa(info->exit_status, num);
	info->var_head->val = num;
}
