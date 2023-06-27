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
*excludeUnNeedTerminatot - Remove unNeeded terminators from the text end
*@str: the input string.
*Return: the new modified string
*/
char *excludeUnNeedTerminatot(char *str)
{
	int len;

	len = _strlen(str);
	if (str[len - 1] == ' ' || str[len - 1] == '\t' ||
		str[len - 1] == '\n' || str[len - 1] == '\v' ||
		str[len - 1] == '\f' || str[len - 1] == '\r')
	{
		str[len - 1] = '\0';
	}

	return (str);
}

/**
*printInteger - print int
*@num: the input int to be print.
*Return: void
*/
void printInteger(int num)
{
	char str[20];
	int len = 0, digit, i;

	/* Convert the integer to a string of digits in reverse order */
	while (num != 0)
	{
		digit = num % 10;
		str[len++] = digit + '0';
		num /= 10;
	}

	/* Write the string in reverse*/
	for (i = len - 1; i >= 0; i--)
	write(STDOUT_FILENO, &str[i], 1);
}
