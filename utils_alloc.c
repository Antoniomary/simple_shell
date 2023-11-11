#include "shell.h"

/**
 * alloc - a function that allocates memory dynamically for a char pointer.
 * @size: the size to allocate.
 *
 * Return: address of newly allocated memory (success), else NULL (failure).
 */
char *alloc(int size)
{
	return ((char *) malloc(sizeof(char) * size));
}

/**
 * realloc_env - a function that resizes the environment variables..
 * @info: a struct tnat contains necessary information.
 *
 * Return: 0 (success), else 1 (failure).
 */
int realloc_env(list *info)
{
	int i;
	char **new = NULL;

	new = (char **) malloc(sizeof(char *) * (info->env_size + 2));
	if (!new)
	{
		errno = ENOMEM;
		_perror(SH_NAME, info->nth_line, NULL, NULL, "can't set ", info->argv[1]);
		return (1);
	}

	info->env_size++;
	for (i = 0; info->env[i]; ++i)
		new[i] = info->env[i];

	new[i] = NULL;
	free(info->env);
	info->env = new;

	return (0);
}

/**
 * _realloc - a function that resizes dynamically allocated memory.
 * @ptr: old memory block to be resized.
 * @old_size: original size of ptr.
 * @new_size: the new size to make ptr.
 *
 * Return: address of allocated memory block or NULL.
 */
void *_realloc(void *ptr, int old_size, int new_size)
{
	int i; /* variable for indexing */
	char *new_ptr = NULL;

	if (!ptr) /* equivalent to ordinary malloc */
		return (malloc(new_size));
	if (!new_size) /* call to free ptr */
	{
		free(ptr);
		return (NULL);
	}
	if (old_size == new_size) /* nothing to do */
		return (ptr);

	/* if (new_size > old_size) */
	/* copy contents of old block to new block */
	new_ptr = malloc(sizeof(char) * new_size);
	if (new_ptr)
	{
		for (i = 0; i < old_size; ++i)
			new_ptr[i] = ((char *) ptr)[i];

		free(ptr);
	}

	return (new_ptr);
}
