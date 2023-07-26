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
	char *executable;
	pid_t pid;

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
		executable = find_executable(arguments[0]);
		handle_redirection(arguments);

		result = execve(executable, arguments, environ);

		/* check if command was executed as intended */
		if (result == -1)
		{
			perror("Failed To Execute Command!\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process waits for child process */
		waitpid(pid, NULL, 0);
	}
}
