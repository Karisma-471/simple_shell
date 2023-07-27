#include "main.h"

/**
 * find_path - searches through the directories to find a command
 * Return: absolute path to the command if found, else NULL
 */
char *find_path(void)
{
	int count = 0;
	char **path_val = _getenv("PATH");
	char **path_dir, *abs_path;

	if (access(command[0], F_OK) == 0)
		return (_strdup(command[0]));

	if (!path_val)
		return (NULL);

	path_dir = _strtok(path_val[1], ':');

	free_array(path_val);

	for (count = 0; path_dir[count]; count++)
	{
		abs_path = malloc(1024);
		_strcpy(abs_path, path_dir[count]);
		_strcat(abs_path, "/");
		_strcat(abs_path, command[0]);

		if (access(abs_path, F_OK) == 0)
		{
			free(abs_path);
			free(path_dir);
			return (abs_path);
		}
		free(abs_path);
	}
	free_array(path_dir);

	return (NULL);
}

