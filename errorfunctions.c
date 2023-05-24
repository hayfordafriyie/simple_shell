#include  "main.h"

/**
 * _errputchar - function which writes a character to the
 *             standard error stream
 * @s: represents the character to be written
 *
 * Return: 1 if successful, otherwise -1
 */

int _errputchar(char s)
{
	static char buffer[WRITE_BUF_SIZE];
	static int p;

	if (s == BUFFER_FLUSH || p >= WRITE_BUF_SIZE)
	{
		write(2, buffer, p);
		p = 0;
	}
	if (s != BUFFER_FLUSH)
	{
		buffer[p++] = s;
	}
	return (1);
}

/**
 * put_c_fd - function that writes a character to  fd with
 *             buffering
 * @c: represents the character to be written
 * @fd: represents the file descriptor
 *
 * Return: 1 on success, otherwise -1
 */

int put_c_fd(char c, int fd)
{
	static char buffer[WRITE_BUF_SIZE];
	static int p;

	if (c == BUFFER_FLUSH || p >= WRITE_BUF_SIZE)
	{
		write(fd, buffer, p);
		p = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[p++] = c;
	return (1);
}

/**
 * put_s_fd - function that writes a string to the fd with
 *            bufffering
 * @string: rep the string to be written
 * @fd: the file descriptor to which the string should be written
 *
 * Return: number of characters successfully written, or 0 if `str` is NULL.
 */

int put_s_fd(char *string, int fd)
{
	int p = 0;

	if (!string)
	{
		return (0);
	}
	while (*string)
	{
		p = p + put_c_fd(*string++, fd);
	}
	return (p);
}

/**
 * _errputs - function which writes a string to standard error
 *
 * @string: the string to be written
 *
 * Return: void
 */

void _errputs(char *string)
{
	int p = 0;

	if (!string)
	{
		return;
	}
	while (string[p] != '\0')
	{
		_errputchar(string[p]);
		p++;
	}
}
