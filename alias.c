#include "main.h"

/**
 * modify_alias - function which replaces the value of an alias
 * in a given structure
 * @data: points to the command_t structure
 *
 * Return: 1 if it is modified, otherwise 0
 */
int modify_alias(command_t *data)
{
	listn_t *node;
	int x;
	char *pt;

	for (x = 0 ; x < 10 ; x++)
	{
		node = find_node_prefix(data->aliases, data->argv[0], '=');
		if (!node)
		{
			return (0);
		}
		free(data->argv[0]);
		pt = _strchr_(node->str, '=');
		if (!pt)
			return (0);
		pt = _strdup_(pt + 1);
		if (!pt)
			return (0);
		data->argv[0] = pt;
	}
	return (1);
}
/**
 * detect_chain - function which detects the chaining operators
 * in a buffer the updates the structure
 *
 * @data: points to the command_t structure
 * @buffer: the char buffer
 * @ptr: points to current buffer position
 *
 * Return: 1 if chain is a delimeter, otherwise 0
 */
int detect_chain(command_t *data, char *buffer, size_t *ptr)
{
	size_t b = *ptr;

	if (buffer[b] == '|' && buffer[b + 1] == '|')
	{
		buffer[b] = 0;
		b++;
		data->comm_buff_type = COMMAND_OR;
	}
	else if (buffer[b] == '&' && buffer[b + 1] == '&')
	{
		buffer[b] = 0;
		b++;
		data->comm_buff_type = COMMAND_AND;
	}
	else if (buffer[b] == ';')
	{
		buffer[b] = 0;
		data->comm_buff_type = COMMAND_CHAIN;
	}
	else
		return (0);
	*ptr = b;
	return (1);
}

/**
 * verify_chain - checks the command chaining
 *           type and modifies the buffer position
 * @data: this points to the command_t struct
 * @buf: buffer with cmd str
 * @pt: points to current position
 * @n: index shows starting position of current cmd
 * @len: the length of buffer
 *
 * Return: void
 */
void verify_chain(command_t *data, char *buf, size_t *pt, size_t n, size_t len)
{
	size_t s = *pt;

	if (data->comm_buff_type == COMMAND_AND)
	{
		if (data->exec_status)
		{
			buf[n] = 0;
			s = len;
		}
	}
	if (data->comm_buff_type == COMMAND_OR)
	{
		if (!data->exec_status)
		{
			buf[n] = 0;
			s = len;
		}
	}

	*pt = s;
}
/**
 * substitute_var - function which replaces variables in a structure
 * with their corresponding values
 * @data: points to the command_t struct
 *
 * Return: 1 if substituted, otherwise 0
 */
int substitute_var(command_t *data)
{

	listn_t *node;
	int p = 0;

	for (p = 0 ; data->argv[p] ; p++)
	{
		if (data->argv[p][0] != '$' || !data->argv[p][1])
			continue;

		if (!_strcmp_(data->argv[p], "$?"))
		{
			update_string(&(data->argv[p]),
				_strdup_(num_to_base(data->exec_status, 10, 0)));
			continue;
		}
		if (!_strcmp_(data->argv[p], "$$"))
		{
			update_string(&(data->argv[p]),
				_strdup_(num_to_base(getpid(), 10, 0)));
			continue;
		}
		node = find_node_prefix(data->envs, &data->argv[p][1], '=');
		if (node)
		{
			update_string(&(data->argv[p]),
				_strdup_(_strchr_(node->str, '=') + 1));
			continue;
		}
		update_string(&data->argv[p], _strdup_(""));

	}
	return (0);
}
/**
 * update_string - function which  replaces what is in a string
 * @prev: the before string
 * @new: the new string
 *
 * Return: 1 if  it is replaced, otherwise 0
 */
int update_string(char **prev, char *new)
{
	free(*prev);
	*prev = new;
	return (1);
}

