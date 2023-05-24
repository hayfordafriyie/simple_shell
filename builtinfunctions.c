#include "main.h"

/**
 * _setAlias - function that sets or updates an alias
 * @data: points to comand_t struct
 * @string: points to string with alias to be set
 *
 * Return: Always 0 on success, otherwise 1 on error
 */
int _setAlias(command_t *data, char *string)
{
	char *pt;

	pt = _strchr_(string, '=');
	if (!pt)
	{
		return (1);
	}
	if (!*++pt)
		return (_unsetAlias(data, string));

	_unsetAlias(data, string);
	return (append_node(&(data->aliases), string, 0) == NULL);
}
/**
 * _unsetAlias - function that unsets alias
 * @data: points to the command_t struct
 * @string: points to str with alias to be unset
 *
 * Return: Always 0 on success, otherwise 1 on error
 */
int _unsetAlias(command_t *data, char *string)
{
	char *pt;
	char s;
	int value;

	pt = _strchr_(string, '=');
	if (!pt)
		return (1);
	s = *pt;
	*pt = 0;
	value = unlink_node_at_index(&(data->aliases),
		find_node_index(data->aliases, find_node_prefix(data->aliases, string, -1)));
	*pt = s;
	return (value);
}
/**
 * display_alias - function that prints alias string
 * @node: alias node
 *
 * Return: Always 0 on success, otherwise 1 on error
 */
int display_alias(listn_t *node)
{
	char *ptr = NULL;
	char *alias = NULL;

	if (node)
	{
		ptr = _strchr_(node->str, '=');
		for (alias = node->str ; alias <= ptr ; alias++)
			_putchar(*alias);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * handle_alias - function that shows alias based on command line args
 * @data: points to the commanf_t struct
 *
 * Return: Always 0
 */
int handle_alias(command_t *data)
{

	char *pt = NULL;
	listn_t *node = NULL;
	int h = 0;

	if (data->argc == 1)
	{
		node = data->aliases;
		while (node)
		{
			display_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (h = 1 ; data->argv[h] ; h++)
	{
		pt = _strchr_(data->argv[h], '=');
		if (pt)
			_setAlias(data, data->argv[h]);
		else
			display_alias(find_node_prefix(data->aliases, data->argv[h], '='));
	}

	return (0);
}
/**
 * show_history - function that shows the history list
 *
 * @data: points to the command_t struct
 *
 * Return: Always 0
 */
int show_history(command_t *data)
{
	display_list(data->hist);
	return (0);
}
