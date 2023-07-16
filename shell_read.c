#include "shell_main.h"

/**
*  _read - A function that reads the arguments
* Return: success
*
*/
int _read(void)
{
	char *cmd = NULL;
	char *cmd_cpy = NULL;
	char *token = NULL;

	char *delim = " \n";
	size_t buffer_size = 0;
	int argc = 0;
	int count = 0;

	char **argv = NULL;

	if (getline(cmd, &buffer_size, stdin) == -1)
		return (-1);

	cmd_cpy = strdup(cmd);

	token = strtok(cmd, delim);

	while (token)
	{
		token = strtok(NULL, delim);
		argc++;
	}

	printf("arguments: %d\n", argc);

	argv = malloc(sizeof(char *) * argc);

	if (argv == NULL)
		perror("Failed to allocate memory");

	token = strtok(cmd_cpy, delim);

	while (token)
	{
		argv[count] = token;
		token = strtok(NULL, delim);
		count++;
	}
	argv[count] = NULL;

	count = 0;
	while (argv[count])
	{
		printf("%s\n", argv[count]);
		count++;
	}

	free(argv), free(cmd), free(cmd_cpy), free(token);
	return (1);
}
