#include "main.h"

/**
 * _calloc - allocates memory to an array
 * @nmemb: number of array elements
 * @size: size of bytes to be alloctated to each nmemb elements
 * Return: a pointer to the allocated memory.
*/
void *_calloc(unsigned int nmemb, unsigned int size)
{
	 void *arr;
	 unsigned int count;

	if (nmemb == 0 || size == 0)
		return (NULL);

	arr = malloc(nmemb * size);
	if (!arr)
		return (NULL);

	for (count = 0; count < (nmemb * size); count++)
		((char *) (arr))[count] = 0;

	return (arr);
}
