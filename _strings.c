#include "main.h"

/**
 * _strdup_ - function that duplicates a string
 * @s: the string to be duplicated
 *
 * Return: a pointer to the duplicated string
 */
char *_strdup_(const char *s)
{
	char *result;
	int len = 0;

	if (s == NULL)
	{
		return (NULL);
	}
	while (*s++)
		len++;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	for (len++; len--;)
		result[len] = *--s;
	return (result);
}
/**
 * _strcpy_ - function that copies a string
 * @dest: pointer to destination string
 * @src: pointer to source string
 *
 * Return: pointer to destination (dest)
 */
char *_strcpy_(char *dest, char *src)
{
	int p = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[p])
	{
		dest[p] = src[p];
		p++;
	}
	dest[p] = 0;
	return (dest);
}
/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static char buffer[WRITE_BUF_SIZE];
	static int i;

	if (c == BUFFER_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[i++] = c;
	return (1);
}
/**
 *_puts - function that prints an string to standard output
 *@s: the string to print
 *
 * Return: void
 */
void _puts(char *s)
{
	int index = 0;

	if (!s)
		return;
	while (s[index] != '\0')
	{
		_putchar(s[index]);
		index++;
	}
}

