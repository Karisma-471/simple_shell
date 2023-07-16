#ifndef _SHELL_MAIN_H
#define _SHELL_MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stddef.h>

int main(void);
void welcome(void);
void print_args(char **string);
int _read(void);
void loop(void);

#endif
