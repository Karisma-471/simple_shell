#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <sys/wait.h>
#include <limits.h>


#define _INT_MIN (1 << (sizeof(int) * 8 - 1))

/* function declaration */
char *find_path(void);
int handle_builtin(void);
int arraycpy(char *dest[], char *src[]);
int exec_command(void);
int printarray(char *array[]);
char **_getenv(char *);
void free_array(char **arr);
int _fputchar(int fd, char c);
int _fputint(int fd, int num);
int _fputstr(int fd, char *str);
int _fprintf(int fd, const char *format, char *s1, int n1, char *s2);
char **_strtok(char *str, char delim);
int print_prompt(char *prompt);
void _printf(char *format, char *replace);
ssize_t _get_line(char **line);
ssize_t _getchar(char c);
int exiting(char *exit_status);
int _atoi(const char *str);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *_strdup(char *str);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
int _strncmp(const char *str1, const char *str2, size_t n);
void *_calloc(unsigned int nmemb, unsigned int size);

/*global variables */
extern char **environ;
int status;
char *line;
char **command;
int shell_index;
char *shell;


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


void *_calloc(unsigned int nmemb, unsigned int size)
{
	void *arr;
	unsigned int count;

	if (nmemb == 0 || size == 0)
		return (NULL);

	arr = malloc(nmemb * size);
	if (!arr)
	{
		return (NULL);
	}

	for (count = 0; count < (nmemb * size); count++)
		((char *) (arr))[count] = 0;

	/* added */
	free(arr);
	return (arr);
}


int exec_command(void)
{
	char *command_path;
	pid_t pid;
	int exit_status;

	if (command[0] && handle_builtin())
	{
		command_path = find_path();
		if (command_path)
		{
			pid = fork();
			if (pid == -1)
			{
				return (0);
			}
			else if (pid == 0)
			{
				execve(command_path, command, environ);
				perror("execve");
				free(command_path);
				exit(EXIT_FAILURE);
			}
			else
			{
				waitpid(pid, &exit_status, 0);
				if (WIFEXITED(exit_status))
					status = WEXITSTATUS(exit_status);
			}
		}
		else
		{
			_fprintf(2, "%a: %b: %c: not found\n", shell, shell_index, command[0]);
			/* added here */
			/*free(command_path);*/
			return (127);
		}
		/*free(command_path);*/
	}

	return (status);
}


int exiting(char *exit_status)
{
	if (!exit_status)
	{
		/* free memory */
		/*free(line);*/
		/*free_array(command);*/
		exit(status);
	}

	status = _atoi(exit_status);

	if (status >= 0)
	{
		/* free memory */
		/*free(line);*/
		/*free_array(command);*/
		exit(status);
	}

	_fprintf(2, "%a: %b: exit: ", shell, shell_index, "nill");
	_fprintf(2, "Illegal number: %a\n", exit_status, 0, "nill");

	return (2);
}

char *find_path(void)
{
	int count = 0;
	char **path_val = _getenv("PATH");
	char **path_dir, *abs_path;

	if (access(command[0], F_OK) == 0)
		return (_strdup(command[0]));

	if (!path_val)
		return (NULL);

	path_dir = _strtok(path_val[1], ':');

	free_array(path_val);

	for (count = 0; path_dir[count]; count++)
	{
		abs_path = malloc(1024);
		_strcpy(abs_path, path_dir[count]);
		_strcat(abs_path, "/");
		_strcat(abs_path, command[0]);

		if (access(abs_path, F_OK) == 0)
		{

			/*free_array(path_dir);*/
			/* added */
			free(abs_path);
			return (abs_path);
		}
		/*free(abs_path);*/
	}
	/* removed */
	/*free_array(path_dir); */
	free(abs_path);

	return (NULL);
}


void free_array(char **arr)
{
	int count;

	if (!arr)
		return;

	for (count = 0; arr[count] != NULL; count++)
		free(arr[count]);

	free(arr);
}


char **_getenv(char *var)
{
	int count;
	char **variable = NULL;

	for (count = 0; environ[count]; count++)
	{
		variable = _strtok(environ[count], '=');
		if (!_strcmp(variable[0], var))
		{

			return (variable);
		}
		/*free_array(variable);*/
	}
	return (variable);
}


ssize_t _get_line(char **line)
{
	char *buf = _calloc(8096, sizeof(char));
	ssize_t n = 0;

	while ((read(0, &buf[n], 1)) > 0 && (buf[n] != '\n'))
		n++;

	if (buf[n] == '\n')
	{
		*line = malloc(sizeof(char) * (n + 1));
		buf[n] = '\0';
		_strcpy(*line, buf);
		/* added */
		free(line);
		free(buf);
		return (n);
	}
	else if (n != 0)
	{
		buf[n] = '\0';
		*line = malloc(sizeof(char) * (n + 1));
		_strcpy(*line, buf);
		/* added */
		free(line);
		free(buf);
		return (-1);
	}
	else
	{
		if (isatty(0))
			_fprintf(1, "\n", "nill", 0, "nill");
		free(buf);
		exit(status);
	}
}


int handle_builtin(void)
{
	if (!command[0])
		return (0);
	if (!_strcmp(command[0], "exit"))
	{
		status = exiting(command[1]);
		return (0);
	}

	if (!_strcmp(command[0], "env"))
	{
		printarray(environ);
		return (0);
	}

	return (-1);
}


int main(int argc, char *argv[])
{
	shell = argv[0];
	shell_index = 0;
	status = 0;

	(void)argc;
	while (++shell_index)
	{
		/* print teh prompt */
		print_prompt("karismaG$: ");

		/* get the arguments from stdin */
		_get_line(&line);

		/* tokenize the commands */
		command = _strtok(line, ' ');

		/* execute the command */
		status = exec_command();

		/* free all the memory used */
		/*free(line);*/
		/*free_array(command);*/
	}

	return (status);
}


int print_prompt(char *prompt)
{
	if (isatty(0))
		_fputstr(1, prompt);

	return (0);
}


int _fputchar(int fd, char c)
{
	return (write(fd, &c, 1));
}


int _fputstr(int fd, char *str)
{
	int i;

	if (!str)
		return (_fputstr(fd, "(null)"));
	for (i = 0; str[i]; i++)
		_fputchar(fd, str[i]);

	return (i);
}

int _fputint(int fd, int num)
{
	int val, len = 0;

	if (!num)
	{
		len += _fputchar(fd, '0');
		return (len);
	}
	if (num == _INT_MIN)
	{
		len += _fputstr(fd, "-2147483648");
		return (len);
	}
	if (num < 0)
	{
		len += _fputchar(fd, '-');
		num = -num;
	}

	val = num % 10;
	num = num / 10;
	if (num)
		len += _fputint(fd, num);
	len += _fputchar(fd, val + '0');

	return (len);
}


int _fprintf(int fd, const char *format, char *s1, int n1, char *s2)
{

	int i = 0, len = 0;

	while (format[i])
	{
		if (format[i] != '%')
			len += _fputchar(fd, format[i]);
		else
		{
			i++;
			if (format[i] == 'a')
				len += _fputstr(fd, s1);
			else if (format[i] == 'b')
				len += _fputint(fd, n1);
			else if (format[i] == 'c')
				len += _fputstr(fd, s2);
		}
		i++;
	}

	return (len);
}


int printarray(char *array[])
{
	int i = 0;

	while (array[i])
	{
		_fprintf(1, "%a\n", array[i], 0, "nill");
		i++;
	}
	return (0);
}


char *_strcat(char *dest, char *src)
{
	int destIndx = 0, srcIndx = 0;

	for (; dest[destIndx] != '\0'; destIndx++)
		;
	for (; src[srcIndx] != '\0'; srcIndx++)
	{
		dest[destIndx] = src[srcIndx];
		destIndx++;
	}
	dest[destIndx] = '\0';
	return (dest);
}


char *_strcpy(char *dest, char *src)
{
	int a;

	for (a = 0; src[a] != '\0'; a++)
		dest[a] = src[a];
	dest[a] = '\0';
	return (dest);
}


char *_strdup(char *str)
{
	char *ptr_alloc, *ptr_alloc_char;
	size_t len;

	if (!str)
		return (NULL);

	for (len = 0; str[len]; len++)
		;

	ptr_alloc = malloc(sizeof(char) * len + 1);
	if (!ptr_alloc)
	{
		/*added */
		/*free(ptr_alloc);*/
		return (NULL);
	}

	ptr_alloc_char = ptr_alloc;

	while (*str)
	{
		*ptr_alloc_char = *str;
		str++;
		ptr_alloc_char++;
	}
	*ptr_alloc_char = '\0';
	/* added */
	free(ptr_alloc);
	return (ptr_alloc);
}


int _strcmp(char *s1, char *s2)
{
	int i = 0;

	for (; s1[i] != '\0' || s2[i] != '\0'; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}
	return (0);
}


int _strlen(char *s)
{
	int len = 0;

	while (*s != '\0')
	{
		s++;
		len++;
	}
	return (len);
}


char **_strtok(char *str, char delim)
{
	int i = 0, j = 0, k = 0;
	int str_len = _strlen(str);
	char **arr = (char **)malloc(sizeof(char *) * (str_len + 1));
	char *buf = (char *)malloc(sizeof(char) * (str_len + 1));


	for ( ; i < str_len + 1; i++)
	{
		if (str[i] != delim && str[i] != '\0')
		{
			buf[k] = str[i];
			k++;
		}
		else
		{
			if (k > 0)
			{
				buf[k] = '\0';
				arr[j] = malloc(sizeof(char) * (k + 1));
				_strcpy(arr[j], buf);
				/* added */
				free(arr[j]);
				j++;
				k = 0;
			}
		}
	}

	arr[j] = NULL;
	free(buf);
	/* added */
	free(arr);
	return (arr);
}


int _strncmp(const char *str1, const char *str2, size_t n)
{
	size_t x;

	for (x = 0; x < n; x++)
	{
		if (str1[x] == '\0' || str2[x] == '\0')
			return (str1[x] - str2[x]);

		if (str1[x] != str2[x])
			return (str1[x] - str2[x]);
	}
	return (0);
}
