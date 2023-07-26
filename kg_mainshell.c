#include "kgshell.h"
void free_com_arg(char *command, char **arguments);
/**
 * main - build a simple shell that takes in prompts
 * @argc: argument count
 * @argv: argument vector.
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	char *command, **arguments;
	FILE *input_file = stdin;
	int interactive = isatty(fileno(input_file));

	if (argc == 2)
	{
		input_file = fopen(argv[1], "r");
		if (input_file == NULL)
			exit(EXIT_FAILURE);
		interactive = 0;
	}
	while (1)
	{
		if (interactive)
			_printf("KARISMA_G$: ", "");
		command = read_command(input_file);
		arguments = parse_command(command);
		if (arguments[0] == NULL)
			free_com_arg(command, arguments);
		if (_strcmp(arguments[0], "exit") == 0)
		{
			free_com_arg(command, arguments);
			break;
		}
		if (_strcmp(arguments[0], "cd") == 0)
		{
			if (chdir(arguments[1]) != 0)
			{
				free_com_arg(command, arguments);
				continue;
			}
		}
		if (interactive)
			handle_pipes(arguments);
		else
			execute_command(arguments);
		free_com_arg(command, arguments);
	}
	if (input_file != stdin)
		fclose(input_file);
	return (0);
}

/**
 * free_com_arg -free's the used memory.
 * @command: the command to be freed.
 * @arguments: the arguments to be freed
 * Return: void
 */

void free_com_arg(char *command, char **arguments)
{

	free(command);
	free(arguments);
}
