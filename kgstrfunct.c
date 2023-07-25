#include "kgshell.h"

/**
* _strlen - calculate the length of a string
* @string: the input string to be used
*
* Return: the length of the string
*/
int _strlen(char *string)
{
	int count = 0;

	while (string[count])
		count++;

	return (count);
}

/**
* _strcmp - a function that compares two strings
* @string1: the first input string
* @string2: the second input string
*
* Return: -1 if string1 < string2, 1 if string1 > string2 and 0 if equal
*/
int _strcmp(char *string1, char *string2)
{
	int count = 0;

	if (strlen(string1) < strlen(string2))
		return (-1);
	else if (strlen(string1) > strlen(string2))
		return (1);

	while (string1[count])
	{
		if (string1[count] != string2[count])
			return (0);
			count++;
	}

	return (0);
}
