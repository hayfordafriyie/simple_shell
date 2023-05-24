#include "main.h"

/**
 * main - function serves as entry point of program
 * @ac: number of command line arguements
 * @av: array of strings with command line arguements
 *
 * Return: 0 on success, otherwise 1 on error
 */
int main(int ac, char **av)
{
	command_t data[] = { DATA_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_errputs(av[0]);
				_errputs(": 0: Cannot open ");
				_errputs(av[1]);
				_errputchar('\n');
				_errputchar(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		data->rd_fd = fd;
	}
	init_env_list(data);
	read_history(data);
	hsh(data, av);
	return (EXIT_SUCCESS);
}
