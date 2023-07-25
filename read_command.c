#include "kgshell.h"

/**
* read_command - a function that reads a line of input
*
* Return: pointer to the dynamically allocated string
*/
char *read_command()
{
	char *string = NULL;
	size_t bufsize = 0;

	/* gets the input from STDIN*/
	if (getline(&string, &bufsize, stdin) == -1)
	{
		if (feof(stdin))
		{
			/* Reached end of file */
			exit(EXIT_SUCCESS);
		}
		else
		{
			/* error occurred*/
			perror("Failed To Get Commands From STDIN\n");
			exit(EXIT_FAILURE);
		}
	}

	return (string);
}
