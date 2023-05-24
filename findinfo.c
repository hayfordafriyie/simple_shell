#include "main.h"

/**
 * initialize_data - this function initializesthe command_t struct
 * with its arguements
 * @data: points to commsnd_t struct
 * @av: arg vector with command line arguements
 */
void initialize_data(command_t *data, char **av)
{
	int p = 0;

	data->filenm = av[0];
	if (data->arg)
	{
		data->argv = splitstr1(data->arg, " \t");
		if (!data->argv)
		{
			data->argv = malloc(sizeof(char *) * 2);
			if (data->argv)
			{
				data->argv[0] = _strdup_(data->arg);
				data->argv[1] = NULL;
			}
		}
		for (p = 0 ; data->argv && data->argv[p] ; p++)
			;
		data->argc = p;

		modify_alias(data);
		substitute_var(data);
	}
}
/**
 * reset_info - function which clears contents of command_t
 * struct and resets to default
 * @data: pointer to struct command_t
 */
void reset_info(command_t *data)
{
	data->arg = NULL;
	data->argv = NULL;
	data->path = NULL;
	data->argc = 0;
}
/**
 * data_free - function which frees the command_t structure
 * @data: points to the command_t structure
 * @full: true if freeing all fields
 */
void data_free(command_t *data, int full)
{
	free_arr(data->argv);
	data->argv = NULL;
	data->path = NULL;
	if (full)
	{
		if (!data->comm_buff)
			free(data->arg);
		if (data->envs)
			release_list(&(data->envs));
		if (data->hist)
			release_list(&(data->hist));
		if (data->aliases)
			release_list(&(data->aliases));
		free_arr(data->environ);
			data->environ = NULL;
		let_free((void **)data->comm_buff);
		if (data->rd_fd > 2)
			close(data->rd_fd);
		_putchar(BUFFER_FLUSH);
	}
}


