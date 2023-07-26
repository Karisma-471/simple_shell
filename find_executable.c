#include "kgshell.h"

/**
* find_executable - a function that finds the path of an executable command
* @command: the command to find
*
* Return: pointer to the path of the executable command or NULL if not found
*/
char *find_executable(char *command)
{
	char *dir, *path, *executable;
	struct stat s;
	/* Check if command is absolute or relative path */
	if (stat(command, &s) == 0)
	{
		if (s.st_mode & S_IXUSR)
			return (_strdup(command));
	}

	/* Check if the command is in PATH environment variable */
	path = getenv("PATH");

	if (path == NULL)
		return ('\0');

	/* tokenize the directory string out of the PATH=value*/
	dir = strtok(path, ":");

	while (dir != NULL)
	{
		/* +2 for '/' and null terminator */
		executable = (char *)malloc(_strlen(dir) + _strlen(command) + 2);
		/* TODO: write the data to executable using a loop */
		sprintf(executable, "%s/%s", dir, command);
		/* checks if the current dir tokenized matches the command*/
		if (stat(executable, &s) == 0)
		{
			if (s.st_mode & S_IXUSR)
				return (executable);
		}

		free(executable);
		dir = strtok(NULL, ":");
	}

	return (executable);
}
