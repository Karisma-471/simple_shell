#ifndef KGSHELL_H
#define KGSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>

#define DELIM " \t\r\n\a"
#define MAX_ARGUMENTS 64

void welcome(void);
void goodbye(void);
void _printf(char *format, char *replace);
int _strlen(char *string);
int _strcmp(char *string1, char *string2);
void execute_command(char **arguments);
char *read_command();
char **parse_command(char *command);
char *find_executable(char *command);
void handle_redirection(char **arguments);
void handle_pipes(char **arguments);
extern char **environ;

#endif
