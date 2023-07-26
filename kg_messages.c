#include "kgshell.h"

/**
 * welcome - prints the welcome message
 * Return: void
 */

void welcome(void)
{
	_printf(" _______________________________________\n", "");
	_printf("|                                       |\n", "");
	_printf("|   WELCOME TO KARISMA_G SIMPLE SHELL   |\n", "");
	_printf("|                                       |\n", "");
	_printf(" --------------------------------------- \n", "");
	_printf("                                         \n", "");
	_printf("TYPE 'HELP' TO LEARN HOW TO USE THE SHELL\n", "");
	_printf("                                          \n", "");
	_printf("----------------> ENJOY <--------------- \n", "");
}

/**
 * goodbye - prints the parting message
 * Return: void
 */

void goodbye(void)
{
	_printf("--------------->GOODBYE<----------------\n", "");
}
