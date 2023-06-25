#include "shell.h"

/**
*printString - print string into stdout
*@str: the string that we will get it's length.
*Return: the lenght of the string / -1 if error
*/
int printString(char* str)
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

char* _strdup(char *str)
{
    int len, i;
    char *newStr = NULL;

    len = _strlen(str);
    newStr = malloc (sizeof(char*) * (len + 1));

    if (newStr == NULL)
    return NULL;

    for(i = 0; i <= len; i++)
    {
        newStr[i] = str[i];
    }
    return newStr;
}
