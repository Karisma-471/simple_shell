#include "main.h"

/**
 * exiting - exits the shell with a status
 * @exit_status: the exit status
 * Return: exits the shell and other cases return 2
 */
int exiting(char *exit_status)
{
	if (!exit_status)
	{
		/* free memory */
		free(line);
		free_array(command);
		exit(status);
	}

	status = _atoi(exit_status);

	if (status >= 0)
	{
		/* free memory */
		free(line);
		free_array(command);
		exit(status);
	}

	_fprintf(2, "%a: %b: exit: ", shell, shell_index, "nill");
	_fprintf(2, "Illegal number: %a\n", exit_status, 0, "nill");

	return (2);
}

