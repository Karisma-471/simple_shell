#include "kgshell.h"

/**
* _printf - a function that simulatesa basic version of printf
* for character substitution
* @format: the format string to be used
* @replace: the string used for substitution
*
* Return: 0 on success
*/
void _printf(char *format, char *replace)
{
	int in_loop = 0;
	int out_loop = 0;
	char current_char;

	while (format[out_loop])
	{
		if (format[out_loop] == '%')
		{
			out_loop += 2;

			while (replace[in_loop])
			{
				current_char = replace[in_loop];
				write(1, &current_char, 1);
				in_loop++;
			}
		}
		else
		{
			current_char = format[out_loop];
			write(1, &current_char, 1);
			out_loop++;
		}
	}
}
