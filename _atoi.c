#include "main.h"

/**
 * _atoi - function that converts string to integer
 *
 * @str: string to be converted
 *
 * Return: 0 if there are no numbers in string, otherwise
 *         the converted number is returned
 */

int _atoi(char *str)
{
	int p;
	int flag = 0;
	int sign = 1;
	int display;
	unsigned int product = 0;

	for (p = 0 ; str[p] != '\0' && flag != 2 ; p++)
	{
		if (str[p] == '-')
			sign *= -1;

		if (str[p] >= '0' && str[p] <= '9')
		{
			flag = 1;
			product = product * 10;
			product += (str[p] - '0');
		}
		else if (flag == 1)
		{
			flag = 2;
		}
	}

	if (sign == -1)
		display = -product;
	else
		display = product;

	return (display);
}

/**
 * _isalpha - function which looks out for an alphabetic
 *          character
 * @c: character to be inserted
 *
 * Return: 1 if it is alphabetic character, otherwise 0
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * is_delimeter - function which checks whether a character is a
 *                delimeter
 * @c: the character to be checked
 * @delimeter: delimeter string
 *
 * Return: 1 if it is true otherwise 0
 */

int is_delimeter(char c, char *delimeter)
{
	while (*delimeter)
		if (*delimeter++ == c)
			return (1);
	return (0);
}

/**
 * is_interactive - function which returns true if the shell
 *                  is in interactive mode
 *
 * @data: the address of the struct
 *
 * Return: 1 if it is interactive, otherwise o
 */
int is_interactive(command_t *data)
{
	return (isatty(STDIN_FILENO) && data->rd_fd <= 2);
}


