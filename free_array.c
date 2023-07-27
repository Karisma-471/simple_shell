#include "main.h"

/**
 * free_array - a function that frees the memmory allocated to an array
 * @arr: the array to be freed
 * Return: void
 */
void free_array(char **arr)
{
	int count;

	if (!arr)
		return;

	for (count = 0; arr[count] != NULL; count++)
		free(arr[count]);

	free(arr);
}

