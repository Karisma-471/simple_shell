#include "shell_main.h"
/**
  * forkexec - A program that executes command in child process
  * @args: Array of characters
  * Return: 1 on success
  * prints out error to stderr if process fails
  */
int forkexec(char **args)
{
	pid_t mypid;
	int status, exe;
	char *comd;

	if (args[0] == NULL)
	{
		return (1);
	}

	mypid = fork();
	if (mypid == -1)
	{
		perror(args[0]);
		return (1);
	}

	if (mypid == 0)
	{
		comd = find_path(args[0]);
		exe = execve(comd, args, environ);
		if (exe == -1)
		{
			perror(args[0]);
			return (0);
		}
	}
	else
	{
		wait(&status);
	}
	return (-1);
}
