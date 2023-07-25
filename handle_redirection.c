#include "kgshell.h"

/**
* handle_redirection - a function that handles the input and output
* redirection for shell commands
* @arguments: Array of strings representing the commands and arguments
*
* Return: 0 on success
*/
void handle_redirection(char **arguments)
{
	int input_fd = -1;
	int output_fd = -1;
	int i = 0;

	while (arguments[i] != NULL)
	{
		if (_strcmp(arguments[i], "<") == 0)
		{
			arguments[i] = NULL;
			input_fd = open(arguments[i + 1], O_RDONLY);
			if (input_fd < 0)
			{
				perror("Failed To Open File");
				exit(EXIT_FAILURE);
			}
			dup2(input_fd, 0);
			close(input_fd);
		}
		else if (_strcmp(arguments[i], ">") == 0)
		{
			/* Remove the "<" from the argument list */
			arguments[i] = NULL;
			output_fd = open(arguments[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (output_fd < 0)
			{
				perror("Failed To Open File\n");
				exit(EXIT_FAILURE);
			}
			dup2(output_fd, 1);
			close(output_fd);
		}
		i++;
	}
}
