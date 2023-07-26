#include "kgshell.h"
/**
* main - build a simple shell that takes in prompts
* Return: 0 on success
*/
int main(void)
{
	char *command, **arguments;

	/*welcome();*/
	/*_printf("\n", "");*/
	while (1)
	{
		_printf("KARISMA_G$: ", "");
		command = read_command();
		if (command[0] == '\0')
		{
			free(command);
			continue;
		}
		arguments = parse_command(command);
		if (arguments[0] == NULL)
		{
			free(command);
			free(arguments);
			continue;
		}
		if (_strcmp(arguments[0], "exit") == 0)
		{
			free(command);
			free(arguments);
			break;
		}
		if (_strcmp(arguments[0], "cd") == 0)
		{
			if (chdir(arguments[1]) != 0)
			free(command);
			free(arguments);
			continue;
		}
		handle_pipes(arguments);
		free(command);
		free(arguments);
	}
	/*goodbye();*/
	return (0);
}
