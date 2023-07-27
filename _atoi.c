#include "main.h"

/**
 * _atoi -  a function that converts a string to integers
 * @str: the string to be converted
 * Return: the resulting integer
 */
int _atoi(const char *str)
{
	int result = 0;
	int sign = 1;
	int count = 0;

	if (str[0] == '-')
	{
		sign = -1;
		count++;
	}

	while (str[count] != '\0')
	{
		if (str[count] < '0' || str[count] > '9')
		return (-2);

		result = result * 10 + (str[count] - '0');
		count++;
	}

	return (sign * result);
}

