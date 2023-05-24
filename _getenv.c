#include "main.h"

/**
 * _setenv_ - function which sets the value for an environment
 *            variable
 *
 * @data: points to the structure with arguments to be used
 * @envar: the string to compare with env variables
 * @value: the string with value assigned to variable
 *
 * Return: Always 0 if successful
 */
int _setenv_(command_t *data, char *envar, char *value)
{
	listn_t *node;
	char *buffer = NULL;
	char *ptr;

	if (!envar || !value)
	{
		return (0);
	}

	buffer = malloc(_strlen_(envar) + _strlen_(value) + 2);
	if (!buffer)
		return (1);
	_strcpy_(buffer, envar);
	_strcat_(buffer, "=");
	_strcat_(buffer, value);
	node = data->envs;
	while (node)
	{
		ptr = is_prefix(node->str, envar);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buffer;
			data->envs_change = 1;
			return (0);
		}
		node = node->next;
	}
	append_node(&(data->envs), buffer, 0);
	free(buffer);
	data->envs_change = 1;
	return (0);
}
/**
 * _getenviron - function which retreives the array of environmental variables
 * @data: points to the structure containing potential arguments
 *
 * Return: Always 0
 */
char **_getenviron(command_t *data)
{
	if (!data->environ || data->envs_change)
	{
		data->environ = list_to_array(data->envs);
		data->envs_change = 0;
	}

	return (data->environ);
}

/**
 * rm_env_variable - function which removes an environment variable
 *                  from a linked list of environmental variables
 * @data: points to the structure with potential arguments.
 * @envar: the string to compare with the env variables in list
 *
 * Return: 1 when deleted, otherwise 0
 *
 */

int rm_env_variable(command_t *data, char *envar)
{
	size_t n = 0;
	char *pt;
	listn_t *node = data->envs;

	if (!node || !envar)
		return (0);

	while (node)
	{
		pt = is_prefix(node->str, envar);
		if (pt && *pt == '=')
		{
			data->envs_change = unlink_node_at_index(&(data->envs), n);
			n = 0;
			node = data->envs;
			continue;
		}
		node = node->next;
		n++;
	}
	return (data->envs_change);
}

