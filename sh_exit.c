#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
*sh_exit - built in function to exit shell with / without exit status.
*@arg: string argument
*@status: pointer to an integer argument status that is used to indicate the
*exit status of the program.
*Return: 0 if success & non-zero if error
*/

int sh_exit(char *arg, int *status)
{
int exit_status = 0;

if (arg)
{
/*If there is an argument, attempt to convert it to an integer*/
exit_status = sh_atoi(arg);
if (exit_status == 0 && arg[0] != '0')
{
/*Conversion failed, set exit status to 2 and print error message*/
*status = 2;
sh_puts("Error: invalid exit status");
return (-1);
}
}
else
{
/*Conversion succeeded, set exit status and return -2 */
*status = exit_status;
return (-2);
}
{
/* No argument provided, set exit status to 0 and return -2*/
*status = 0;
return (-2);
}
}


/**
 *sh_putchar - writes the character c to stdout
 *@c: The character to print
 *Return: On success 1.
 *On error, -1 is returned, and errno is set appropriately.
 */
int sh_putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 *sh_puts - to prints a string to stdout.
 *@str: a pointer to string.
 *Return: void.
 */

void sh_puts(char *str)
{
	int i = 0;
	char *arr;

	arr = str;

	while (arr[i])
	{
		sh_putchar(arr[i]);
		i++;
	}
	sh_putchar('\n');
}



/**
 *sh_atoi - get the in from string.
 *@s: a pointer to string.
 *Return: int.
 */
int sh_atoi(char *s)
{
	int length = 0;
	int sign = 1;
	int i = 0;
	int num = 0;

	while (s[i])
	{
		length++;
		i++;
	}

	for (i = 0; i < length; i++)
	{
		if (s[i] == '-')
		{
			sign = sign * -1;
		}
		if (s[i] >= 48 && s[i] <= 57)
		{
			num = num * 10 + (s[i] - 48);

			if (!((s[i + 1] >= 48) && (s[i + 1] <= 57)))
			{
				break;
			}
		}
	}

	num = num * sign;
	return (num);
}
