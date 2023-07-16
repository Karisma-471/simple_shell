#include "shell_main.h"

/**
* main - creating our version of the shell
* Return: 0 on success and -1 if fails
*/
int main(void)
{
	/* print the welcome message once at the start of the shell */
	welcome();

	/* loops the prompt and executes commands */
	loop();

	printf("See You Again\n");

	return (0);
}
