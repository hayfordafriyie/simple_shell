#include "main.h"

/**
 * _changeDirectory - function which changes the current working
 *           directory
 * @data: the struct with the arguments to be used
 *
 * Return: Always 0
 */

int _changeDirectory(command_t *data)
{
	char *cwd;
	char *dir;
	char buffer[1024];
	int result;

	cwd = getcwd(buffer, 1024);
	if (!cwd)
		_puts("TODO: >>getcwd failure emsg <<\n");
	if (!data->argv[1])
	{
		dir = search_env(data, "HOME=");
		if (!dir)
			result = chdir((dir = search_env(data, "PWD=")) ? dir : "/");
		else
			result = chdir(dir);
	}
	else if (_strcmp_(data->argv[1], "-") == 0)
	{
		if (!search_env(data, "OLDPWD="))
		{
			_puts(cwd);
			_putchar('\n');
			return (1);
		}
		_puts(search_env(data, "OLDPWD="));
		_putchar('\n');
		result = chdir((dir = search_env(data, "OLDPWD=")) ? dir : "/");
	}
	else
		result = chdir(data->argv[1]);
	if (result == -1)
	{
		display_error(data, "can't cd to ");
		_errputs(data->argv[1]), _errputchar('\n');
	}
	else
	{
		_setenv_(data, "OLDPWD", search_env(data, "PWD="));
		_setenv_(data, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * print_help - function which changes the directory to help
 * @data: points to command_t struct
 *
 *  Return: Always 0
 */
int print_help(command_t *data)
{
	char **arg_arr;

	arg_arr = data->argv;
	_puts("help can be executed. Function under development \n");
	if (0)
		_puts(*arg_arr);
	return (0);
}

/**
 * _exitprogram - function which exits the program
 * @data: points to command_t structure with args
 *
 *  Return:  this exits with  exit status
 *         (0) if info.argv[0] != "exit"
 */
int _exitprogram(command_t *data)
{
	int exitcode;

	if (data->argv[1])
	{
		exitcode = err_atoi(data->argv[1]);
		if (exitcode == -1)
		{
			data->exec_status = 2;
			display_error(data, "Illegal number: ");
			_errputs(data->argv[1]);
			_errputchar('\n');
			return (1);
		}
		data->error_num = err_atoi(data->argv[1]);
		return (-2);
	}
	data->error_num = -1;
	return (-2);
}


