#include "kgshell.h"

/**
* parse_command - a function that tokenizes a command string into array
* of strings
* @command: the command string to be parsed
*
* Return: An array of strings
*/
char **parse_command(char *command)
{
	int count = 0;
	char *token;
	/* allocates memory for the array of strings holding the commands*/
	char **tokens = malloc(_strlen(command) * sizeof(char *));
	/* check if malloc allocated correctly */
	if (!tokens)
	{
		perror("Failed To Allocate Memory\n");
		exit(EXIT_FAILURE);
	}

	/* tokenize the command so you can separate command from arguments*/
	token = strtok(command, DELIM);

	while (token != NULL)
	{
		tokens[count] = token;
		count++;
		token = strtok(NULL, DELIM);
	}
	tokens[count] = NULL;

	return (tokens);
}
