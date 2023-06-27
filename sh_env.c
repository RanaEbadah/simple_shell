#include "shell.h"

/**
 *print_current_enviroment- prints the elements of each node in a linked list
 *@head: pointer to the first node of the linked list
 *Return: the number of nodes in the linked list
 */
size_t print_current_enviroment(const list_t *head)
{
size_t i = 0;
int *next;

for (; head != NULL; head = head->next, i++)
{
sh_puts(head->str ? head->str : "(nil)");
}
return (i);
}

/**
 *sh_env - print the current enviroment list
 *@list: structure of function argument
 *Return: Always return (0)
*/
int sh_env(list_t *list)
{
print_current_enviroment(data->env);
return (0);
}
