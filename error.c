#include "main.h"

/**
 * print_integer - function that prints an integer value
 *                  to a file descriptor
 * @value: the integer to be printed
 * @fd: rep the file desctiptor where to write output
 *
 * Return: the count of characters printed including digits and
 *          other characters
 */

int print_integer(int value, int fd)
{
	int p;
	int (*printChar)(char) = _putchar;
	int total = 0;
	unsigned int absvalue;
	unsigned int curr;

	if (fd == STDERR_FILENO)
		printChar = _errputchar;
	if (value < 0)
	{
		absvalue = -value;
		printChar('-');
		total++;
	}
	else
		absvalue = value;
	curr = absvalue;
	for (p = 1000000000 ; p > 1 ; p /= 10)
	{
		if (absvalue / p)
		{
			printChar('0' + curr / p);
			total++;
		}
		curr %= p;
	}
	printChar('0' + curr);
	total++;

	return (total);
}

/**
 * display_error - function that prints an error message to the
 *        standard error output
 * @data: a pointer to structure command_t
 * @errorinfo: points to the character array with error message
 *             to be printed
 * Return: 0 if no numbers are found. if found the converted integer
 *         otherwise -1
 */

void display_error(command_t *data, char *errorinfo)
{
	_errputs(data->filenm);
	_errputs(": ");
	print_integer(data->line_number, STDERR_FILENO);
	_errputs(": ");
	_errputs(data->argv[0]);
	_errputs(": ");
	_errputs(errorinfo);
}
/**
 * err_atoi - function that converts the srting rep of an int
 *        to its numerical value
 * @str: the string to convert
 *
 * Return: 0 if no numbers are found, if found the return converted integer
 *         otherwise -1
 */

int err_atoi(char *str)
{
	unsigned long int output = 0;
	int p = 0;

	if (*str == '+')
		str++;
	for (p = 0 ; str[p] != '\0' ; p++)
	{
		if (str[p] >= '0' && str[p] <= '9')
		{
			output = output * 10;
			output += (str[p] - '0');
			if (output > INT_MAX)/*max value in int data type*/
				return (-1);
		}
		else
			return (-1);
	}
	return (output);
}

/**
 * num_to_base - function that coverts a given number to a
 *              specified base
 * @number: the number converted
 * @base: the specified base
 * @flag: the flag used
 *
 * Return: the converted string
 */

char *num_to_base(long int number, int base, int flag)
{
	char sign = 0;
	static char *arr;
	static char buffer[50];
	unsigned long b = number;
	char *pt;


	if (!(flag & SWITCH_UNSIGNED) && number < 0)
	{
		b = -number;
		sign = '-';

	}
	arr = flag & CONVERT_TO_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pt = &buffer[49];
	*pt = '\0';

	do	{
		*--pt = arr[b % base];
		b /= base;
	} while (b != 0);

	if (sign)
		*--pt = sign;
	return (pt);
}
/**
 * delete_comments - remove comments at first instance of '#'
 *                 and replaces it with '\0'
 * @str: the string from which comments are removed
 *
 * Return: Always 0
 */

void delete_comments(char *str)
{
	int p;

	for (p = 0 ; str[p] != '\0' ; p++)
		if (str[p] == '#' && (!p || str[p - 1] == ' '))
		{
			str[p] = '\0';
			break;
		}
}
