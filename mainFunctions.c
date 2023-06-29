#include "shell.h"


/**
*notFound - display not Found error
*@shellName: the input string.
*@errorNum: the number of the error.
*@commandName: the command name.
*Return: the number of the coming error
*/
int notFound(char *shellName, int errorNum, char *commandName)
{
	int errorMsgLen, shellNamelen, commandNameLen;
	char errorMsg[] = ": not found\n";
	char *errorNumptr;

	if ((shellName == NULL) || (commandName == NULL))
	return (-1);

	errorNumptr = malloc(sizeof(int));
	if (errorNumptr == NULL)
	{
		return (-1);
	}

	*errorNumptr = errorNum;
	errorMsgLen = _strlen(errorMsg);
	shellNamelen = _strlen(shellName);
	commandNameLen = _strlen(commandName);

	write(2, shellName, shellNamelen);
	write(2, ": ", 2);
	printInteger(errorNum, 2);
	write(2, ": ", 2);
	write(2, commandName, commandNameLen);
	write(STDOUT_FILENO, errorMsg, errorMsgLen);

	errorNum++;
	free(errorNumptr);
	return (errorNum);
}


/**
*exitTheShell - exit the shell.
*@exitStatus: 1 if exit command, 0 if ctrl+D
*/
void exitTheShell(int exitStatus)
{
	if (!exitStatus)
	printString("\n");
	/*free(line);*/
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
	int status, executed, i = 0;
	pid_t pid;

	pid = fork();/*we will execute the command*/
	if (pid == -1)
	return (1);
	else if (pid == 0)
	{
		while (args[i] != NULL)
		{
			args[i] = excludeUnNeedTerminatot(args[i]);
			i++;
		}
		executed = execve(filePath, args, envp);
		if (executed == -1)
		{
			perror(NULL);
			exit (1);
		}
	}
	else /*it is a parent*/
	wait(&status);
	return (0);
}


/**
*executeCommand - execute the command
*@path: the path
*@args: arguments
*@envp: envp parameter
*@argv: argv parameter
*@errorNum: the number of the error
*Return: void
*/
void executeCommand(char *path,
char **args, char **envp, char **argv, int *errorNum)
{
	char *argsStr, *exitStr = "exit", *envStr = "env", *filePath;

	argsStr = excludeUnNeedTerminatot(args[0]);
	if (_strcmp(argsStr, exitStr) == 0)
	{
		free(args);
		exitTheShell(1);
	}
	else if (_strcmp(argsStr, envStr) == 0)
	_getEnv(envp);
	else
	{
		filePath = isExec(path, args[0]);
		if (filePath == NULL)
		*errorNum = notFound(argv[0], *errorNum, args[0]);
		else
		executeTheExecCommand(filePath, args, envp);
	}
	free(args);
}
