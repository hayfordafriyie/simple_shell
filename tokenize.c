#include "main.h"


/**
 * **splitstr2 - function that splits a string into words
 *
 * @string: the input string to be split
 * @delim: the delimeter
 *
 * Return:  pointer to an array of strings, otherwise NULL
 */
char **splitstr2(char *string, char delim)
{
	int r, p;
	int q, chcount, wdcount = 0;
	char **result;

	if (string == NULL || string[0] == 0)
		return (NULL);
	for (r = 0 ; string[r] != '\0'; r++)
		if ((string[r] != delim && string[r + 1] == delim) ||
		    (string[r] != delim && !string[r + 1]) || string[r + 1] == delim)
			wdcount++;
	if (wdcount == 0)
		return (NULL);
	result = malloc((1 + wdcount) * sizeof(char *));
	if (!result)
		return (NULL);
	for (r = 0, p = 0 ; p < wdcount ; p++)
	{
		while (string[r] == delim && string[r] != delim)
			r++;
		q = 0;
		while (string[r + q] != delim && string[r + q] && string[r + q] != delim)
			q++;
		result[p] = malloc((q + 1) * sizeof(char));
		if (!result[p])
		{
			for (q = 0; q < p; q++)
				free(result[q]);
			free(result);
			return (NULL);
		}
		for (chcount = 0 ; chcount < q ; chcount++)
			result[p][chcount] = string[r++];
		result[p][chcount] = 0;
	}
	result[p] = NULL;
	return (result);
}

/**
 * **splitstr1 - function that splits a string into words
 * and ignores repeated delimeters
 * @s: the input string to be split
 * @del: the delimeter string used to split string
 *
 * Return: pointer to an array of strings, otherwise NULL
 */

char **splitstr1(char *s, char *del)
{
	int r, p, q;
	int chcount, wdcount = 0;
	char **result;

	if (s == NULL || s[0] == 0)
		return (NULL);
	if (!del)
		del = " ";
	for (r = 0 ; s[r] != '\0' ; r++)
		if (!is_delimeter(s[r], del) && (is_delimeter(s[r + 1], del) || !s[r + 1]))
			wdcount++;

	if (wdcount == 0)
		return (NULL);
	result = malloc((1 + wdcount) * sizeof(char *));
	if (!result)
		return (NULL);
	for (r = 0, p = 0 ; p < wdcount ; p++)
	{
		while (is_delimeter(s[r], del))
			r++;
		q = 0;
		while (!is_delimeter(s[r + q], del) && s[r + q])
			q++;
		result[p] = malloc((q + 1) * sizeof(char));
		if (!result[p])
		{
			for (q = 0 ; q < p ; q++)
				free(result[q]);
			free(result);
			return (NULL);
		}
		for (chcount = 0 ; chcount < q ; chcount++)
			result[p][chcount] = s[r++];
		result[p][chcount] = 0;
	}
	result[p] = NULL;
	return (result);
}

