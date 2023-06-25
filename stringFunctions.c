#include "shell.h"

/**
*_strlen - get the length of a string.
*@str: the string that we will get it's length.
*Return: the lenght of the string / -1 if the sting is null
*
*/
int _strlen(char *str)
{
	int i = 0;

	if (str == NULL)
	return (-1);

	while (str[i] != '\0')
	i++;

	return (i);
}

/**
*concat_string - concatenate two strings.
*@dest: first string.
*@src: second string.
*Return: concatenated string / NULL -error
*
*/
char *concat_string(char *dest, char *src)
{
	char *resultStr;
	int destlen, srcLen;
	int i = 0;
	int j = 0;

	if ((dest == NULL) || (src == NULL))
	return (NULL);

	destlen = _strlen(dest);
	srcLen = _strlen(src);

	if ((destlen < 0) || (srcLen < 0))
	return (NULL);

	resultStr = malloc((srcLen + destlen + 1) * sizeof(char));

	if (resultStr == NULL)
	return (NULL);

	for (i = 0; i < (srcLen + destlen); i++)
	{
		if (i < destlen)
		{
			resultStr[i] = dest[i];
		}
		else
		{
			if (j < srcLen)
			{
				resultStr[i] = src[j];
				j++;
			}
		}
	}
	resultStr[i] = '\0';
	return (resultStr);
}

/**
*_strcpy - copy source string to destination.
*@dest: first string.
*@src: second string.
*Return: copied string / NULL -error
*/
char *_strcpy(char *dest, char *src)
{
	char *ptr;
	int srcLen;

	if ((dest == NULL) || (src == NULL))
	return (NULL);

	srcLen = _strlen(src);
	dest = realloc(dest, (srcLen + 1));

	ptr = dest;
	while (*src != '\0')
	{
		*ptr = *src;
		ptr++;
		src++;
	}
	*dest = '\0';
	return (dest);
}

/**
*_strcmp - compare two strings.
*@str1: first string.
*@str2: second string.
*Return: 0 if equal
*1 if str1>str2, -1 if str2 > str1
*/
int _strcmp(char *str1, char *str2)
{
	int i = 0;

	while ((str1[i] != '\0') && (str2[i] != '\0'))
	{
		if (str1[i] > str2[i])
		return (1);
		else if (str1[i] < str2[i])
		return (-1);
		else
		i++;
	}

	if ((str1[i] == '\0') && (str2[i] == '\0'))
	return (0);
	else if (str1[i] == '\0')
	return (-1);
	else
	return (1);
}

/**
*_strncmp - compare first n characters from two strings.
*@str1: first string.
*@str2: second string.
*@n: The number of characters
*Return: 0 if equal
*1 if str1>str2, -1 if str2 > str1
*/
int _strncmp(char *str1, char *str2, int n)
{
	int i = 0;

	while ((str1[i] != '\0') && (str2[i] != '\0') && (i < n))
	{
		if (str1[i] > str2[i])
		return (1);
		else if (str1[i] < str2[i])
		return (-1);
		else
		i++;
	}

	if (i == n)
	return (0);

	if ((str1[i] == '\0') && (str2[i] == '\0'))
	return (0);
	else if (str1[i] == '\0')
	return (-1);
	else
	return (1);
}
