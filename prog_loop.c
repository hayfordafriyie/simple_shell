#include "main.h"

/**
 * fork_exec - function which executes a command in child
 *               process
 * @data: pointer to associated struct
 *
 * Return: nothing 0
 */

void fork_exec(command_t *data)
{
	pid_t child;

	child = fork();
	if (child == -1)
	{
		perror("Error:");
		return;
	}
	if (child == 0)
	{
		if (execve(data->path, data->argv, _getenviron(data)) == -1)
		{
			data_free(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(data->exec_status));
		if (WIFEXITED(data->exec_status))
		{
			data->exec_status = WEXITSTATUS(data->exec_status);
			if (data->exec_status == 126)
				display_error(data, "Permission denied\n");
		}
	}
}

/**
 * get_cmd - function which gets a command in a specific
 *            PATH
 * @data: points to the command_t struct
 *
 * Return: nothing
 */
void get_cmd(command_t *data)
{
	int p, r;
	char *path = NULL;


	data->path = data->argv[0];
	if (data->linenumber_flag == 1)
	{
		data->line_number++;
		data->linenumber_flag = 0;
	}
	for (p = 0, r = 0 ; data->arg[p] ; p++)
		if (!is_delimeter(data->arg[p], " \t\n"))
			r++;
	if (!r)
		return;

	path = get_path(data, search_env(data, "PATH="), data->argv[0]);
	if (path)
	{
		data->path = path;
		fork_exec(data);
	}
	else
	{
		if ((is_interactive(data) || search_env(data, "PATH=")
			|| data->argv[0][0] == '/') && exec_cmd(data, data->argv[0]))
			fork_exec(data);
		else if (*(data->arg) != '\n')
		{
			data->exec_status = 127;
			display_error(data, "not found\n");
		}
	}
}
/**
 * get_builtin - function which gets and executes builtin commands
 * in the program
 * @data: points to the command_t struct
 *
 * Return: -1 if builtin cmd not found, o if successful, 1 if found
 * but not successful. -2 if signals exit()
 *
 */
int get_builtin(command_t *data)
{
	int x;
	int  output = -1;
	command_table builtintbl[] = {
		{"exit", _exitprogram},
		{"env", display_env},
		{"help", print_help},
		{"history", show_history},
		{"setenv", mod_env_var},
		{"unsetenv", unset_env},
		{"cd", _changeDirectory},
		{"alias", handle_alias},
		{NULL, NULL}
	};

	for (x = 0 ; builtintbl[x].name ; x++)
		if (_strcmp_(data->argv[0], builtintbl[x].name) == 0)
		{
			data->line_number++;
			output = builtintbl[x].func(data);
			break;
		}
	return (output);
}
/**
 * hsh - the entry point of shell program
 * @data: points to struct with arguements
 * @av: pointer to the command line arguemnts array
 *
 * Return: 0 on success, 1if an error occurs, or  the error code
 */
int hsh(command_t *data, char **av)
{
	int cmd_result = 0;
	ssize_t x = 0;

	while (x != -1 && cmd_result != -2)
	{
		reset_info(data);
		if (is_interactive(data))
			_puts("$ ");
		_errputchar(BUFFER_FLUSH);
		x = input_chain(data);
		if (x != -1)
		{
			initialize_data(data, av);
			cmd_result = get_builtin(data);
			if (cmd_result == -1)
				get_cmd(data);
		}
		else if (is_interactive(data))
			_putchar('\n');
		data_free(data, 0);
	}
	store_history(data);
	data_free(data, 1);
	if (!is_interactive(data) && data->exec_status)
		exit(data->exec_status);
	if (cmd_result == -2)
	{
		if (data->error_num == -1)
			exit(data->exec_status);
		exit(data->error_num);
	}
	return (cmd_result);
}


