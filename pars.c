#include "main.h"

/**
 * get_path - this function searches for a given command in the
 * PATH string
 * @data: this points to the command_t structure
 * @pathstring: the specific pathstring to look in
 * @command: the specific command to find
 *
 * Return: the PATH of the command ,otherwise NULL
 */
char *get_path(command_t *data, char *pathstring, char *command)
{
	int p = 0;
	int now = 0;
	char *path;

	if (!pathstring)
	{
		return (NULL);
	}
	if ((_strlen_(command) > 2) && is_prefix(command, "./"))
	{
		if (exec_cmd(data, command))
			return (command);
	}
	while (1)
	{
		if (!pathstring[p] || pathstring[p] == ':')
		{
			path = _substr(pathstring, now, p);
			if (!*path)
				_strcat_(path, command);
			else
			{
				_strcat_(path, "/");
				_strcat_(path, command);
			}
			if (exec_cmd(data, path))
				return (path);
			if (!pathstring[p])
				break;
			now = p;
		}
		p++;
	}
	return (NULL);
}
/**
 * exec_cmd - function that checks if a file is an executable command
 * @data: points to command_t structure
 * @path: the path to file
 *
 * Return: 1 if it is true, otherwise 0
 */
int exec_cmd(command_t *data, char *path)
{
	struct stat st;

	(void)data;
	if (!path || stat(path, &st))
	{
		return (0);
	}

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
 * _substr - function that extracts a substring
 *             from the given string
 * @pathstring: the specific PATH string
 * @begin: the starting index
 * @end: the stopping index
 *
 * Return: a pointer to new buffer with substring
 */
char *_substr(char *pathstring, int begin, int end)
{
	static char buffer[1024];
	int r = 0;
	int p = 0;

	for (p = 0, r = begin ; r < end ; r++)
		if (pathstring[r] != ':')
			buffer[p++] = pathstring[r];
	buffer[p] = 0;
	return (buffer);
}

