#include "main.h"

/**
 * unlink_node_at_index - functions that deletes a node at a
 *                        specific index in a linked list
 * @head: this contains the address of the first node in the
 * list
 * @index: the specific index to delete
 *
 * Return: 1 if successful otherwise 0
 */

int unlink_node_at_index(listn_t **head, unsigned int index)
{
	unsigned int p = 0;
	listn_t *cnode;
	listn_t *b4_node;

	if (!head || !*head)
	{
		return (0);
	}

	if (!index)
	{
		cnode = *head;
		*head = (*head)->next;
		free(cnode->str);
		free(cnode);
		return (1);
	}
	cnode = *head;
	while (cnode)
	{
		if (p == index)
		{
			b4_node->next = cnode->next;
			free(cnode->str);
			free(cnode);
			return (1);
		}
		p++;
		b4_node = cnode;
		cnode = cnode->next;
	}
	return (0);
}

/**
 * display_list_strings - function print the str member of
 * each node in a linked list
 *
 * @head: points to the first node in the list
 *
 * Return: the size of the linked list which is the
 * number of the nodes in there
 */
size_t display_list_strings(const listn_t *head)
{
	size_t p = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		p++;
	}
	return (p);
}

/**
 * release_list - this function frees the memory allocated
 *  for all the nodes in the linked list
 * @head_list: holds the  address of the head node in list
 *
 * Return: Nothing
 */
void release_list(listn_t **head_list)
{
	listn_t *cnode;
	listn_t	*adjacent_node, *head;

	if (!head_list || !*head_list)
		return;
	head = *head_list;
	cnode = head;
	while (cnode)
	{
		adjacent_node = cnode->next;
		free(cnode->str);
		free(cnode);
		cnode = adjacent_node;
	}
	*head_list = NULL;
}
/**
 * append_node - function which adds a node at
 * the end of the list
 *
 * @head: this has the address of pointer to head node
 * @str: the string to be stored in the new node
 * @value: the node index used by history
 *
 * Return: pointer to the newly appended node
 */
listn_t *append_node(listn_t **head, const char *str, int value)
{
	listn_t *nw;
	listn_t *node;

	if (!head)
	{
		return (NULL);
	}

	node = *head;
	nw = malloc(sizeof(listn_t));
	if (!nw)
		return (NULL);
	_memset_((void *)nw, 0, sizeof(listn_t));
	nw->value = value;
	if (str)
	{
		nw->str = _strdup_(str);
		if (!nw->str)
		{
			free(nw);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = nw;
	}
	else
		*head = nw;
	return (nw);
}
/**
 * new_head - function that adds  node to the start of the list
 * @head: the address of pointer to head
 * @str: string to be stored in new node
 * @value: the node index used by history
 *
 * Return: a pointer to the newly added node
 */
listn_t *new_head(listn_t **head, const char *str, int value)
{
	listn_t *nw_hd;

	if (!head)
	{
		return (NULL);
	}
	nw_hd = malloc(sizeof(listn_t));
	if (!nw_hd)
		return (NULL);
	_memset_((void *)nw_hd, 0, sizeof(listn_t));
	nw_hd->value = value;
	if (str)
	{
		nw_hd->str = _strdup_(str);
		if (!nw_hd->str)
		{
			free(nw_hd);
			return (NULL);
		}
	}
	nw_hd->next = *head;
	*head = nw_hd;
	return (nw_hd);
}
