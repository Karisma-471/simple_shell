#include "kgshell.h"

/**
* read_command - a function that reads a line of input
* @file: the file to be evaluated
* Return: pointer to the dynamically allocated string
*/
char *read_command(FILE *file)
{
	char *string = NULL;
	size_t bufsize = 0;

	/* gets the input from STDIN*/
	if (getline(&string, &bufsize, file) == -1)
	{
		return (_strdup(""));
	}

	return (string);
}
