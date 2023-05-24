#include "main.h"

/**
 * let_free -  function that frees a pointer and
 *             sets address to NULL
 * @p: address of the pointer to freed and set to NULL
 *
 * Return: 1 memory is freed, otherwise 0.
 */
int let_free(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
