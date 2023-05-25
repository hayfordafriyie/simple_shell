#include "main.h"

/**
 * find_node_index - function which finds the index of
 *                     a node in a linked lists
 * @h: this points to list head
 * @node: this points  to the node
 *
 * Return: the index of node, otherwise -1
 */
ssize_t find_node_index(listn_t *h, listn_t *node)
{
	size_t ind = 0;

	while (h)
	{
		if (h == node)
		{
			return (ind);
		}
		h = h->next;
		ind++;
	}
	return (-1);
}
/**
 * find_node_prefix - function finds a node which starts with a specific
 *                    prefix or char
 * @node: pointer to list head
 * @pref: the string to match
 * @c: the character to check after prefix
 *
 * Return: the matched node otherwise NULL
 */
listn_t *find_node_prefix(listn_t *node, char *pref, char c)
{
	char *pt = NULL;

	while (node)
	{
		pt = is_prefix(node->str, pref);
		if (pt && ((c == -1) || (*pt == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
/**
 * display_list - function which prints the content of a linked
 *               list
 * @head: points to the first node
 *
 * Return: the total number of nodes
 */
size_t display_list(const listn_t *head)
{
	size_t i = 0;

	while (head)
	{
		_puts(num_to_base(head->value, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		i++;
	}
	return (i);
}
/**
 * list_to_array - function which coverts a linked list to an array of
 *                 strings
 * @head: points to the first node
 *
 * Return: the array of strings
 */
char **list_to_array(listn_t *head)
{
	listn_t *nd = head;
	size_t i = list_count(head);
	size_t r;
	char **st;
	char *s;

	if (!head || !i)
	{
		return (NULL);
	}
	st = malloc(sizeof(char *) * (i + 1));
	if (!st)
		return (NULL);
	for (i = 0 ; nd ; nd = nd->next, i++)
	{
		s = malloc(_strlen_(nd->str) + 1);
		if (!s)
		{
			for (r = 0 ; r < i ; r++)
				free(st[r]);
			free(st);
			return (NULL);
		}

		s = _strcpy_(s, nd->str);
		st[i] = s;
	}
	st[i] = NULL;
	return (st);
}
/**
 * list_count - function that counts the number of nodes
 *               in a linked list
 * @head: this points to first node
 *
 * Return: the total number of nodes
 */
size_t list_count(const listn_t *head)
{
	size_t p = 0;

	while (head)
	{
		head = head->next;
		p++;
	}
	return (p);
}

