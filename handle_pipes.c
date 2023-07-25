#include "kgshell.h"

/**
* handle_pipes - a function that executes multiple shell commands
* connected by pipes
* @arguments: array of strings representing the commands and arguments
* Return: 0 on success
*
*/
void handle_pipes(char **arguments)
{
	int pipe_count = 0;
	int loop = 0;
	int commands_count = 0;
	pid_t *pids;

	/* Count the number of pipes */
	while (arguments[loop] != NULL)
	{
		if (_strcmp(arguments[loop], "|") == 0)
		{
		/* Replace "|" with NULL to separate commands */
			arguments[loop] = NULL;
			pipe_count++;
		}
		loop++;
	}
	/* if no pipe is passed as argument, execute simple command*/
	if (pipe_count == 0)
	{
		execute_command(arguments);
		return;
	}

	commands_count = pipe_count + 1;
	pids = malloc(commands_count * sizeof(pid_t));
	if (!pids)
	{
		perror("Failed To Allocate Memory\n");
		exit(EXIT_FAILURE);
	}
	/* Input for the first command is STDIN */
	int pipe_fds[2];
	int input_fd = 0;
	int status;
	int i = 0;

	while (i < commands_count)
	{
		if (i < pipe_count)
		{
			if (pipe(pipe_fds) == -1)
			{
				perror("No Pipes in Command\n");
				exit(EXIT_FAILURE);
			}
		}

		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("Failed To Fork The Second Piped Command\n");
			exit(EXIT_FAILURE);
		}

		if (pids[i] == 0)
		{
			/* Child process */
			if (i > 0)
			{
				/* set the input to the read end of the previous pipe */
				dup2(input_fd, 0);
				close(input_fd);
			}

			if (i < pipe_count)
			{
				/* set the output to the write end of the current pipe */
				dup2(pipe_fds[1], 1);
				close(pipe_fds[0]);
				close(pipe_fds[1]);
			}

			execute_command(arguments + i);

			exit(EXIT_SUCCESS);
		}
		else
		{
			/* Parent process */
			if (i > 0)
			{
				/* Close the read end of the previous pipe */
				close(input_fd);
			}

			if (i < pipe_count)
			{
				/* Close the write end of the current pipe */
				close(pipe_fds[1]);
				input_fd = pipe_fds[0];
			}
		}
		i++;
	}

	/* Parent process wait for all child processes to complete */
	for (int i = 0; i < commands_count; i++)
	{
		waitpid(pids[i], &status, 0);
	}

	free(pids);
}
