#include "kgshell.h"

int count_pipes(char **arguments);
void execute(int pipe_cnt, int commands_count, pid_t *pids, char **arguments);

/**
 * handle_pipes - a function that executes multiple shell commands
 * connected by pipes
 * @arguments: array of strings representing the commands and arguments
 * Return: 0 on success
 *
 */
void handle_pipes(char **arguments)
{
	int pipe_cnt = 0, status, i = 0, commands_count = 0;
	pid_t *pids;

	pipe_cnt = count_pipes(arguments);

	if (pipe_cnt == 0)
	{
		execute_command(arguments);
		return;
	}
	commands_count = pipe_cnt + 1;
	pids = malloc(commands_count * sizeof(pid_t));
	if (!pids)
	{
		perror("Failed To Allocate Memory\n");
		exit(EXIT_FAILURE);
	}

	execute(pipe_cnt, commands_count, pids, arguments);

	for ( ; i < commands_count; i++)
		waitpid(pids[i], &status, 0);

	free(pids);
}

/**
 * count_pipes - counts the number of pipes passed to args
 * @arguments: the arguments passed to the shell
 * Return: return the number of pipes in the argument
 **/
int count_pipes(char **arguments)
{
	int pipe_count = 0;
	int loop = 0;

	while (arguments[loop] != NULL)
	{
		if (_strcmp(arguments[loop++], "|") == 0)
		{
			arguments[loop] = NULL;
			pipe_count++;
		}
	}

	return (pipe_count);
}

/**
 * execute - forks the process and executes the pipes
 * @pipe_cnt: number of pipes
 * @commands_count: number of commands passed
 * @pids: number of child processes
 * @arguments: argsmpassed to shell
 * Return: void.
 */
void execute(int pipe_cnt, int commands_count, pid_t *pids, char **arguments)
{
	int pipe_fds[2], input_fd = 0, i = 0;

	while (i++ < commands_count)
	{
		if (i < pipe_cnt)
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
			if (i > 0)
			{
				dup2(input_fd, 0);
				close(input_fd);
			}
			if (i < pipe_cnt)
			{
				dup2(pipe_fds[1], 1);
				close(pipe_fds[0]);
				close(pipe_fds[1]);
			}
			execute_command(arguments + i);
			exit(EXIT_SUCCESS);
		}
		else
		{
			if (i > 0)
				close(input_fd);

			if (i < pipe_cnt)
			{
				close(pipe_fds[1]);
				input_fd = pipe_fds[0];
			}
		}
	}
}
