#include "shell_main.h"

/**
* loop - A function that implements the loop of the shell
*/
void loop(void)
{
	int status = 0;

	do {
		printf("Karism_G$ ");
		status = _read();
	} while (status);
}
