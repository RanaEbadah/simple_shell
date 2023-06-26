#include "shell.h"

/**
*printString - print string into stdout
*@str: the string that we will get it's length.
*Return: the lenght of the string / -1 if error
*/
int printString(char *str)
{
	int len;
	ssize_t written;

	if (str == NULL)
	return (-1);

	len = _strlen(str);
	written =  write(1, str, len);

	if (written == -1)
	return (-1);

	return (written);
}


/**
*_strdup - create a new string by duplicating an existing string
*@str: the string that will be copied.
*Return: the new string
*/
char *_strdup(char *str)
{
	int len, i;
	char *newStr = NULL;

	len = _strlen(str);
	newStr = malloc(sizeof(char *) * (len + 1));

	if (newStr == NULL)
	return (NULL);

	for (i = 0; i <= len; i++)
	{
		newStr[i] = str[i];
	}
	return (newStr);
}

/**
*_getLine - the implementation of getline.
*@line: pointer to character buffer that will receive the input.
*@s: the buffer size.
*@stream: pointer to input stream read from
*Return: number of readed bytes
*/
ssize_t _getLine(char **line, size_t *s, void *stream)
{
	static char buffer[1024];
	static int pos;
	static int size;
	int fd;
	size_t count = 0;
	char c;
	intptr_t intptr;

	pos = 0;
	size = 0;
	intptr = (intptr_t)stream;
	fd = (int) intptr;
	printf("fd is %d\n", fd);
	if ((line == NULL) || (*line == NULL) || (*s == 0))
	return (-1);
	while (1)
	{
		if (pos >= size) /*check if u have to read some data to the buffer*/
		{
			size = read(fd, buffer, 1024);
			if ((size < 0) || (size == 0))
			return (-1);
		}
		c = buffer[pos];
		(*line)[count] = c;
		pos++;
		count++;
		if (c == '\n') /*end of line*/
		break;
		if (count == *s)
		{
			*line = realloc(*line, (*s + 1024));
			if (*line == NULL)
			return (-1);
		}
		*s = *s + 1024;
	}
	(*line)[count] = '\0';
	return (count);
}
