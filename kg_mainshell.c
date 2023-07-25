#include "kg_mainshell.c"

/**
* main - build a simple shell that takes in prompts
* @argc: argument count to be used
* @argv: argument array to be used
* Return: 0 on success
*/

int main(int argc, char **argv)
{
	char *command, **arguments;
	int status = 1;

	/* printing the welcome message and spacing lines */
	welcome();

	/* print two empty lines after the welcome message */
	_printf("\n", "");
	_printf("\n", "");

	while (status)
	{
	/* print the prompt */
		_printf("KARISMA_G$: ", "");

	/* read the command*/
		command = read_command();
	/* check if no command was passed, free memory and continue */
		if (command[0] == '\0')
		{
			free(command);
			continue;
		}

		/* populate the arguments variable with the parse_commands function */
		arguments = parse_command(command);
		/* check if no command was passed, free memory and continue */
		if (arguments[0] == NULL)
		{
			free(command);
			free(arguments);
			continue;
		}

		/* exit the program if the exit command is called */
		if (_strcmp(arguments[0], "exit") == 0)
		{
			free(command);
			free(arguments);
			break;
		}

		/* change the directory of the parent process*/
		if (_strcmp(arguments[0], "cd") == 0)
		{
			if (chdir(arguments[1]) != 0)
			free(command);
			free(arguments);
			continue;
		}

		/* execute the executable file in stored in the command variable */
		handle_pipes(arguments);
		/* free every memory left..*/
		free(command);
		free(arguments);
	}

	/* print goodbye message */
	goodbye();

	return (0);
}
