#include "main.h"

/**
 * handle_builtin - Handles builtin commands like exit, env, e.t.c
 * Return: 0 for success, else status
 */
int handle_builtin(void)
{
	if (!command[0])
		return (0);
	if (!_strcmp(command[0], "exit"))
	{
		status = exiting(command[1]);
		return (0);
	}

	if (!_strcmp(command[0], "env"))
	{
		printarray(environ);
		return (0);
	}

	return (-1);
}

