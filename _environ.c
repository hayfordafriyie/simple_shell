#include "main.h"

/**
 * search_env - function that retrieves the value
 *  of an environment variable
 *
 * @data: points to the command_t structure
 * @varname: the environment variable name
 *
 * Return: the value of env variable
 */
char *search_env(command_t *data, const char *varname)
{
	listn_t *node = data->envs;
	char *pt;

	while (node)
	{
		pt = is_prefix(node->str, varname);
		if (pt && *pt)
		{
			return (pt);
		}
		node = node->next;
	}
	return (NULL);
}

/**
 * mod_env_var - function that initializes a new environment variable,
 *             or ia able to modify one
 * @data: points to the command_t structure
 *
 *  Return: Always 0
 */
int mod_env_var(command_t *data)
{
	if (data->argc != 3)
	{
		_errputs("Incorrect count of arguements\n");
		return (1);
	}
	if (_setenv_(data, data->argv[1], data->argv[2]))
		return (0);
	return (1);
}
/**
 * unset_env - function that removes an environment variable
 * @data: points to the command_t structure
 *
 *  Return: Always 0
 */
int unset_env(command_t *data)
{
	int p;

	if (data->argc == 1)
	{
		_errputs(" few arguements.\n");
		return (1);
	}
	for (p = 1 ; p <= data->argc ; p++)
		rm_env_variable(data, data->argv[p]);

	return (0);
}
/**
 * display_env - prints the contents of an enviroment variable list
 * @data: this points to the command_t structure
 *         .
 * Return: Always 0
 */
int display_env(command_t *data)
{
	display_list_strings(data->envs);
	return (0);
}
/**
 * init_env_list - function initializes the environment
 *               variable list
 * @data: points to the command_t structure
 *
 * Return: Always 0
 */
int init_env_list(command_t *data)
{
	listn_t *node = NULL;
	size_t s;

	for (s = 0 ; environ[s] ; s++)
		append_node(&node, environ[s], 0);
	data->envs = node;
	return (0);
}

