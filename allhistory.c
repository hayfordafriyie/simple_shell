#include "main.h"

/**
 * store_history - function that creats or write contents of  a list
 *                to an existing file
 *
 * @data: points to the structure to be used
 *
 * Return: 1 if successful, otherwise -1
 */
int store_history(command_t *data)
{
	ssize_t fd;
	listn_t *node = NULL;
	char *name = find_history_file(data);

	if (!name)
	{
		return (-1);
	}

	fd = open(name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(name);
	if (fd == -1)
		return (-1);
	for (node = data->hist; node; node = node->next)
	{
		put_s_fd(node->str, fd);
		put_c_fd('\n', fd);
	}
	put_c_fd(BUFFER_FLUSH, fd);
	close(fd);
	return (1);
}
/**
 * find_history_file - function which finds the history file
 * @data: points to the structure with arguements
 *
 * Return: string with history file
 */

char *find_history_file(command_t *data)
{
	char *buff;
	char *direc;

	direc = search_env(data, "HOME=");
	if (!direc)
	{
		return (NULL);
	}
	buff = malloc(sizeof(char) * (_strlen_(direc) + _strlen_(HISTORY_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy_(buff, direc);
	_strcat_(buff, "/");
	_strcat_(buff, HISTORY_FILE);
	return (buff);
}
/**
 * read_history -  function that reads history from file
 * @data: points to structure command_t with arguements
 *
 * Return: the number of histoty entries if successful,
 *           otherwise 0
 */
int read_history(command_t *data)
{
	int index, lst_ind = 0;
	int linenum = 0;
	ssize_t fd, rd_length, filesize = 0;
	struct stat st;
	char *buffer = NULL;
	char *filename = find_history_file(data);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		filesize = st.st_size;
	if (filesize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (filesize + 1));
	if (!buffer)
		return (0);
	rd_length = read(fd, buffer, filesize);
	buffer[filesize] = 0;
	if (rd_length <= 0)
		return (free(buffer), 0);
	close(fd);
	for (index = 0; index < filesize; index++)
		if (buffer[index] == '\n')
		{
			buffer[index] = 0;
			add_to_history(data, buffer + lst_ind, linenum++);
			lst_ind	= index + 1;
		}
	if (lst_ind != index)
		add_to_history(data, buffer + lst_ind, linenum++);
	free(buffer);
	data->histnum = linenum;
	while (data->histnum-- >= MAX_HISTORY_SIZE)
		unlink_node_at_index(&(data->hist), 0);
	renumber_hist(data);
	return (data->histnum);
}

/**
 * renumber_hist - function which renumbers the history
 *           list after changes
 * @data: points to the structure with potential arguments.
 *
 * Return: new history count
 */
int renumber_hist(command_t *data)
{
	listn_t *node = data->hist;
	int p = 0;

	while (node)
	{
		node->value = p++;
		node = node->next;
	}
	return (data->histnum = p);
}
/**
 * add_to_history - function which adds an  entry to a history  list
 * @data: points to the structure to be used
 * @buffer:  the buffer
 * @linenum: the number of lines in the buffer
 *
 * Return: Always 0 on succes
 */
int add_to_history(command_t *data, char *buffer, int linenum)
{
	listn_t *node = NULL;

	if (data->hist)
		node = data->hist;
	append_node(&node, buffer, linenum);

	if (!data->hist)
		data->hist = node;
	return (0);
}
