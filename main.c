#include "shell.h"

/**
 * main - a function that excecute a simple shell
 *@argc: the number of arguments (unused)
 *@argv: the arguments
 *@envp: env
 * Return: 0 (success)
 */
int main(__attribute__((unused)) int argc,
__attribute__((unused)) char *argv[], char *envp[])
{
	char *line = NULL, *path, **args, **envpCopy = NULL;
	size_t len;
	int  readed;
	static int errorNum;

	errorNum = 1;
	envpCopy = envp;
	path = getPathFromEnv(envpCopy);/*get the path*/
	if (!isatty(STDIN_FILENO)) /*non interactive*/
	{
		while ((readed = getline(&line, &len, stdin)) != -1)
		{
			if (commandIsSpaceOrEnter(line) == 1)
			continue;/*if the input is enter or space continue*/
			args = handleCommandLine(line); /*parse the line to command and arguments*/
			if ((args == NULL) || (path == NULL))
			{
				free(args);
				return (1); }
			executeCommand(path, args, envp, argv, &errorNum); }}
	else
	{
		while (1)
		{
			printString("$ ");
			readed = getline(&line, &len, stdin);
			if (readed == -1) /*EOF handling*/
			exitTheShell(0);
			if (commandIsSpaceOrEnter(line) == 1)
			continue;/*if the input is enter or space continue*/
			args = handleCommandLine(line); /*parse the line to command and arguments*/
			if ((args == NULL) || (path == NULL))
			{
				free(args);
				return (1); }
			executeCommand(path, args, envp, argv, &errorNum); }}
	free(line);
	return (0);
}
