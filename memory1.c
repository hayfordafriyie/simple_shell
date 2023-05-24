#include "main.h"


/**
 * _reallocate - function that resizes apreviously
 *             allocated block of memory
 * @ptr: pointer to the memory block to be resized
 * @oldSize: current size of the memory block
 * @newSize: the desired ne size of memory block
 *
 * Return: a pointer to the resized memory block
 */
void *_reallocate(void *ptr, unsigned int oldSize, unsigned int newSize)
{
	char *new;

	if (!ptr)
		return (malloc(newSize));
	if (!newSize)
		return (free(ptr), NULL);
	if (newSize == oldSize)
		return (ptr);

	new = malloc(newSize);
	if (!new)
		return (NULL);

	oldSize = oldSize < newSize ? oldSize : newSize;
	while (oldSize--)
		new[oldSize] = ((char *)ptr)[oldSize];
	free(ptr);
	return (new);
}

/**
 * _memset_ - function that fills memory with a
 *             specified value byte by byte
 * @m: points to the memory block
 * @x: bytes used to fill the memory block
 * @n: the number of bytes to be set
 *
 * Return: a pointer to the memory area
 */
char *_memset_(char *m, char x, unsigned int n)
{
	unsigned int p;

	for (p = 0 ; p < n ; p++)
		m[p] = x;
	return (m);
}
/**
 * free_arr - function frees memory allocated for
 *        array of strings
 * @pArr: pointer to array of strings
 */
void free_arr(char **pArr)
{
	char **s = pArr;

	if (!pArr)
	{
		return;
	}
	while (*pArr)
		free(*pArr++);
	free(s);
}
