#include "main.h"

/**
 * _strncat_ - function that concatenates two strings
 * @dest: the destination string
 * @src: the source string
 * @b: the number of bytes
 *
 * Return: final concatenated string
 */
char *_strncat_(char *dest, char *src, int b)
{
	int x, k;
	char *st = dest;

	x = 0;
	k = 0;
	while (dest[x] != '\0')
		x++;
	while (src[k] != '\0' && k < b)
	{
		dest[x] = src[k];
		x++;
		k++;
	}
	if (k < b)
		dest[x] = '\0';
	return (st);
}
/**
 * _strncpy_ - function that copies a portion of a string to
 *               another
 * @dest: the destination string
 * @src: the source string to get str
 * @c: the number of characters to be copied
 *
 * Return: dest the concatenated str
 */
char *_strncpy_(char *dest, char *src, int c)
{
	int i;
	int r;
	char *str = dest;

	i = 0;
	while (src[i] != '\0' && i < c - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < c)
	{
		r = i;
		while (r < c)
		{
			dest[r] = '\0';
			r++;
		}
	}
	return (str);
}
/**
 ** _strchr_ - function that searches for first occurence of a char
 *           in a string
 * @str: string to search char in
 * @c: the chars to find
 *
 * Return: (t) the location of matching char in string
 */

char *_strchr_(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}

