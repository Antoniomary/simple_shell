#include "shell.h"

/**
 * creat_alias - a function that creates an alias.
 * @entry: the alias to be created in the form of name=value
 *
 * Return: the address of the new alias else NULL.
 */
alias_t *creat_alias(char *entry)
{
	char *ptr = NULL;
	int i = 0, j = 0, used_quote = false;
	alias_t *new = malloc(sizeof(alias_t));

	if (!new)
		return (NULL);

	/* get name part */
	ptr = _strtok(entry, "=");
	new->name = _strdup(ptr); /* make duplicate of it */
	if (!new->name)
		return (free(new), NULL);
	/* get value part */
	ptr = _strtok(NULL, "\0");
	new->val = alloc(_strlen(ptr) + 1); /* allocate space */
	if (!new->val)
		return (free(new->name), free(new), NULL);
	if (ptr && *ptr) /* user may have value equal to nothing */
	{
		for ( ; ptr[j]; ++j)
		{
			/* skip quote mark if any */
			if (ptr[j] == '\'' || ptr[j] == '"')
				used_quote = ptr[j++];
			/* match closing quote */
			if (used_quote && (ptr[j] == used_quote))
				used_quote = false;
			else
				new->val[i++] = ptr[j];
		}
	}
	new->val[i] = '\0', new->next = NULL;

	/* form the name=value part */
	new->name_val = str_dup_cat(new->name, "=\'", new->val, "'");
	if (!new->name_val)
		return (free(new->name), free(new->val), free(new), NULL);

	return (new);
}

/**
 * add_replace_alias - a function that adds or replaces a new or existing
 * alias respectively.
 * @head: pointer to head node.
 * @new: new or modified alias to be added or replaced.
 *
 * Return: always 0 (success).
 */
int add_replace_alias(alias_t **head, alias_t *new)
{
	alias_t *temp = *head;

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
				free(temp->name_val);
				temp->name_val = new->name_val;
				free(new->name);
				free(new);

				return (0);
			}

			if (!temp->next)
				break;

			temp = temp->next;
		}

		temp->next = new;
	}

	return (0);
}

/**
 * print_alias - a function that prints all the aliases.
 * @head: pointer to the head node.
 *
 * Return: always 0.
 */
int print_alias(alias_t *head)
{
	while (head)
	{
		_puts(head->name_val, 1);
		head = head->next;
	}

	return (0);
}

/**
 * find_print_alias - a function that searches and prints a particular alias.
 * @head: pointer to head node.
 * @name: the name of the alias to be searched for.
 *
 * Return: 0 if it exists, else 1 if not.
 */
int find_print_alias(alias_t *head, char *name)
{
	while (head)
	{
		if (_strcmp(head->name, name) == 0)
		{
			_puts(head->name_val, 1);
			return (0);
		}

		head = head->next;
	}

	eputs("alias: ", name, "not found", 1);

	return (1);
}

/**
 * free_alias - a function that frees a singly linked list.
 * @head: pointer to the head node of the list to free.
 */
void free_alias(alias_t *head)
{
	if (head)
	{
		alias_t *temp = head;

		while (head)
		{
			temp = head;
			head = head->next;
			free(temp->name);
			free(temp->val);
			free(temp->name_val);
			free(temp);
		}
	}
}
