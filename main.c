#include "main.h"

/**
 * main - Entry point
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 for success, others for failure
 */
int main(int argc, char *argv[])
{
	shell = argv[0];
	shell_index = 0;
	status = 0;

	(void)argc;
	while (++shell_index)
	{
		/* print teh prompt */
		print_prompt("karismaG$: ");

		/* get the arguments from stdin */
		if (_get_line(&line) == -1)
		{
			free(line);
			free_array(command);
		}

		/* tokenize the commands */
		command = _strtok(line, ' ');

		/* execute the command */
		status = exec_command();

		free(line);
		free_array(command);
	}

	free(line);
	free_array(command);

	return (status);
}

