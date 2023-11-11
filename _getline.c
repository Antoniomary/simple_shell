#include "shell.h"

#define N 128

/**
 * _getline - a function that gets a line of text from an entry.
 * @line: the place to store each line.
 * @n: size allocatted to line before call to _getline.
 * @fd: file descriptor to the file to retrieve the lines of text from.
 *
 * Return: the number of characters that was gotten else -1 (failure)
 */
int _getline(char **line, size_t *n, int fd)
{
	static char buf[10], *ptr = buf;
	static int bytes_read;
	char *temp = NULL;
	size_t i = 0, bufsize;

	if (!line || !n)
		return (-1);
	*line = (*line == NULL || *n == 0) ? alloc(N) : NULL;
	if (!(*line))
		return (-1);
	bufsize = (*n > 0) ? *n : N;

	do {
		if (bytes_read <= 0) /* reads from fd once */
		{
			bytes_read = read(fd, buf, sizeof(buf));
			/* -1 is read error; 0 is EOF detected */
			if (bytes_read <= 0)
			{
				(*line)[i] = '\0';
				return (bytes_read); /* i.e -1 or 0 */
			}
			ptr = buf;
		}
		/*resizes line as necessary */
		if (i >= bufsize - 1)
		{
			bufsize = !(bufsize % N) ? (bufsize * 2) : ((*n + N) - (*n  % N));
			temp = _realloc(*line, i, bufsize);
			if (!temp)
				return (-1);
			*line = temp;
		}
		/*copies one character at a time from chunk gathered from fd */
		--bytes_read, (*line)[i++] = *ptr++;
	} while ((*line)[i - 1] != '\n');
	(*line)[i] = '\0', *n = bufsize;

	return ((int) i);
}
