#include "main.h"

/**
 * _getenv - Finds a environment variable name and returns it's value
 * @var: The variable name to be found
 * Return: a pointer to the varible's value
 */
char **_getenv(char *var)
{
	int count;
	char **variable = NULL;

	for (count = 0; environ[count]; count++)
	{
		variable = _strtok(environ[count], '=');
		if (!_strcmp(variable[0], var))
		{
			free_array(variable);
			return (variable);
		}
		free_array(variable);
	}
	return (variable);
}

