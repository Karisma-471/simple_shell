#include "kgshell.h"

/**
* execute_command - a function that executes shell command
* @arguments: the arguments to be used for the command
*
* Return: 0 on success
*/
void execute_command(char **arguments)
{
	int result = 0;
	int status;
	char *executable;
	pid_t pid;

	executable = find_executable(arguments[0]);
	/* checking if command exists */
	if (executable == NULL)
	{
		_printf("%s: No such file or directory\n", "./hsh");
		exit(EXIT_FAILURE);
	}

	/* split child and parent process */
	pid = fork();

	if (pid == -1)
	{
		perror("Failed To Create Child Process!\n");
		return;
	}

	if (pid == 0)
	{
		 /* Child process */
		handle_redirection(arguments);

		status = execve(executable, arguments, environ);

		/* check if command was executed as intended */
		if (result == -1)
		{
			perror("Failed To Execute Command!\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	}
		/* Parent process waits for child process */
		waitpid(pid, &status, 0);
	}
}
