#include "main.h"

/**
 * buffer_input -the fumction is responsible for
 *           buffering chained commands
 * @data: points to the struct with arguements
 * @buff: the address of buffer to store input
 * @len: address of len var that rep the length of buffer
 *
 * Return: the number of bytes read
 */
ssize_t buffer_input(command_t *data, char **buff, size_t *len)
{
	size_t allocsize = 0;
	ssize_t p = 0;

	if (!*len)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, handleSIGINT);
#if ENABLE_GETLINE
		p = getline(buf, &allocsize, stdin);
#else
		p = _readline(data, buff, &allocsize);
#endif
		if (p > 0)
		{
			if ((*buff)[p - 1] == '\n')
			{
				(*buff)[p - 1] = '\0';
				p--;
			}
			data->linenumber_flag = 1;
			delete_comments(*buff);
			add_to_history(data, *buff, data->histnum++);
			/* Check if the buffer contains a command chain delimited by ';' */
			{
				*len = p;
				data->comm_buff = buff;
			}
		}
	}
	return (p);
}
/**
 * input_chain- function which retrieves input and handling of
 *             command chaining
 * @data: this points ot the struct used
 *
 * Return: number of bytes resd
 */
ssize_t input_chain(command_t *data)
{
	static char *buf;
	static size_t p;
	static size_t n, len;
	ssize_t q = 0;
	char **bufP = &(data->arg), *pt;

	_putchar(BUFFER_FLUSH);
	q = buffer_input(data, &buf, &len);
	if (q == -1) /* file ends */
		return (-1);
	if (len)
	{
		n = p;
		pt = buf + p; /* get pointer  */

		verify_chain(data, buf, &n, p, len);
		while (n < len)
		{
			if (detect_chain(data, buf, &n))
				break;
			n++;
		}

		p = n + 1;
		if (p >= len) /* end of buffer? */
		{
			p = len = 0; /* reset position and length */
			data->comm_buff_type = COMMAND_DEFAULT;
		}

		*bufP = pt; /* ptr to current command position */
		return (_strlen_(pt));
	}

	*bufP = buf;
	return (q);
}
/**
 * read_buffer - function which reads  buffer
 * @data: points to the struct with arguements command_t
 * @buf: the buffer
 * @p: pointer to size_t var
 *
 * Return: number of bytes read
 */
ssize_t read_buffer(command_t *data, char *buf, size_t *p)
{
	ssize_t rd = 0;

	if (*p)
	{
		return (0);
	}
	rd = read(data->rd_fd, buf, READ_BUF_SIZE);
	if (rd >= 0)
		*p = rd;

	return (rd);
}
/**
 * _readline - function which reads a line  or input from file
 *             descriptor to a buffer
 * @data: points to command_t struct
 * @ptr: address of pointer to buffer
 * @length: points to var rep the length of the input line
 *
 * Return: the length of input line
 */
int _readline(command_t *data, char **ptr, size_t *length)
{
	static char buff[READ_BUF_SIZE];
	static size_t i, len;
	size_t j;
	ssize_t rd = 0;
	ssize_t sl = 0;
	char *p = NULL;
	char *nw = NULL, *c;

	p = *ptr;
	if (p && length)
	{
		sl = *length;
	}
	if (i == len)
		i = len = 0;

	rd = read_buffer(data, buff, &len);
	if (rd == -1 || (rd == 0 && len == 0))
		return (-1);

	c = _strchr_(buff + i, '\n');
	j = c ? 1 + (unsigned int)(c - buff) : len;
	nw = _reallocate(p, sl, sl ? sl + j : j + 1);
	if (!nw)
		return (p ? free(p), -1 : -1);

	if (sl)
		_strncat_(nw, buff + i, j - i);
	else
		_strncpy_(nw, buff + i, j - i + 1);

	sl += j - i;
	i = j;
	p = nw;

	if (length)
		*length = sl;
	*ptr = p;
	return (sl);
}
/**
 * handleSIGINT - the signal handler for SIGINT (Ctrl+C) signal
 * @signal_num: the signal number
 *
 * Return: nothing
 */
void handleSIGINT(__attribute__((unused))int signal_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_FLUSH);
}
