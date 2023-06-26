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
	char *line = NULL, *path, *filePath, **args, *envStr ="env";
	char *argsStr, **envpCopy = NULL, *exitStr = "exit";
	size_t len;
	int executed, readed, errorNum = 1;

	envpCopy = envp;
	path = getPathFromEnv(envpCopy);/*get the path*/
	while (1)
	{
		printf("$ ");
		readed = getline(&line, &len, stdin);
		if (readed == -1) /*EOF handling*/

		exitTheShell(line, 0);
		if (commandIsSpaceOrEnter(line) == 1)
		continue;/*if the input is enter or space continue*/

		args = handleCommandLine(line); /*parse the line to command and arguments*/
		if ((args == NULL) || (path == NULL))
		return (1);

		argsStr = excludeUnNeedTerminatot(args[0]);
		if (_strcmp(argsStr, exitStr) == 0)
		{
			/*exit*/
			exitTheShell(line, 1);
		}
		else if (_strcmp(argsStr, envStr) == 0)
		{
			/*env*/
			printf("This is env command\n");
		}
		else
		{
			filePath = isExec(path, args[0]);
			if (filePath == NULL)
			{
				errorNum = notFound(argv[0], errorNum, args[0]);
				continue;
			}
			else
			{
				executed = executeTheExecCommand(filePath, args, envp);
				if (executed == 1)
				return (1);
			}}}
	return (0);
}

/**
*notFound - display not Found error
*@shellName: the input string.
*@errorNum: the number of the error.
*@commandName: the command name.
*Return: the number of the coming error
*/
int notFound(char *shellName, int errorNum, char *commandName)
{
	printf("%s: %d: %s: not found\n", shellName, errorNum, commandName);
	errorNum++;
	return (errorNum);
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
*exitTheShell - exit the shell.
*@line: the command line(to free it).
*@exitStatus: 1 if exit command, 0 if ctrl+D
*/
void exitTheShell(char *line, int exitStatus)
{
	if (!exitStatus)
	printf("\n");
	free(line);
	exit(0);
}

/**
*executeTheExecCommand - execute the executable commands
*@filePath: the path of the executable file
*@args:arguments
*@envp:env
*Return: 1 if failure, 0 if success
*/
int executeTheExecCommand(char *filePath, char **args, char *envp[])
{
	int status, executed;
	pid_t pid;

	pid = fork();/*we will execute the command*/
	if (pid == -1)
	return (1);
	else if (pid == 0)
	{
		executed = execve(filePath, args, envp);
		if (executed == -1)
		return (1);
	}
	else /*it is a parent*/
	wait(&status);
	return (0);
}
