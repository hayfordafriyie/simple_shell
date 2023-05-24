#include "main.h"

/**
 * _strcat_ - function that  concatenates two strings
 * @dest: a pointer tothe destination buffer
 * @src: pointer to the source buffer
 *
 * Return: pointer to concatenated string
 */
char *_strcat_(char *dest, char *src)
{
	char *output = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (output);/*start of concatenated str*/
}

/**
 * _strlen_ - function that gets the length of a string
 * @str: the string with the length to check
 *
 * Return: the length of string
 */
int _strlen_(char *str)
{
	int s = 0;

	if (!str)
		return (0);

	while (*str++)
		s++;
	return (s);
}
/**
 * is_prefix - function that checks if needle string
 *    is a prefix of haystack string
 * @haystack: points to thestring to search
 * @needle: points to the substring
 *
 * Return: the address of next char in haystack
 * otherwise NULL
 */
char *is_prefix(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
		{
			return (NULL);
		}
	return ((char *)haystack);
}

/**
 * _strcmp_ - function that compares two strangs.
 * @str1: the first strang to compare
 * @str2: the second strang to compare
 *
 * Return: negative if str1 < str2 or positive if str1 > str2
 * or zero if str1 == str2
 */
int _strcmp_(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
	{
		return (0);
	}
	else
		return (*str1 < *str2 ? -1 : 1);
}
