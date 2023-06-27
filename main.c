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
	char *line = NULL, *path, **args;
	char **envpCopy = NULL;
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
			return (1);
			executeCommand(line, path, args, envp, argv, &errorNum);
		}
	}
	else
	{
		while (1)
		{
			printString("$ ");
			readed = getline(&line, &len, stdin);
			if (readed == -1) /*EOF handling*/
			exitTheShell(line, 0);
			if (commandIsSpaceOrEnter(line) == 1)
			continue;/*if the input is enter or space continue*/
			args = handleCommandLine(line); /*parse the line to command and arguments*/
			if ((args == NULL) || (path == NULL))
			return (1);
			executeCommand(line, path, args, envp, argv, &errorNum);
		}
	}
	free(args);
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
	int errorMsgLen, shellNamelen, commandNameLen;
	char errorMsg[] = ": not found\n";
	char *errorNumptr;

	if ((shellName == NULL) || (commandName == NULL))
	return (-1);

	errorNumptr = malloc(sizeof(int));
	if (errorNumptr == NULL)
	return (-1);

	*errorNumptr = errorNum;
	errorMsgLen = _strlen(errorMsg);
	shellNamelen = _strlen(shellName);
	commandNameLen = _strlen(commandName);

	write(STDOUT_FILENO, shellName, shellNamelen);
	write(STDOUT_FILENO, ": ", 2);
	printInteger(errorNum);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, commandName, commandNameLen);
	write(STDOUT_FILENO, errorMsg, errorMsgLen);

	errorNum++;
	free(errorNumptr);
	return (errorNum);
}


/**
*exitTheShell - exit the shell.
*@line: the command line(to free it).
*@exitStatus: 1 if exit command, 0 if ctrl+D
*/
void exitTheShell(char *line, int exitStatus)
{
	if (!exitStatus)
	printString("\n");
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
		return (1);
	}
	else /*it is a parent*/
	wait(&status);
	return (0);
}


/**
*executeCommand - execute the command
*@line: the line which the user entered
*@path: the path
*@args: arguments
*@envp: envp parameter
*@argv: argv parameter
*@errorNum: the number of the error
*Return: void
*/
void executeCommand(char *line, char *path,
char **args, char **envp, char **argv, int *errorNum)
{
	char *argsStr, *exitStr = "exit", *envStr = "env", *filePath;

	argsStr = excludeUnNeedTerminatot(args[0]);
	if (_strcmp(argsStr, exitStr) == 0)
	{
		/* Exit */
		exitTheShell(line, 1);
	}
	else if (_strcmp(argsStr, envStr) == 0)
	{
		/* Env */
		printString("This is the env command\n");
	}
	else
	{
		filePath = isExec(path, args[0]);

		if (filePath == NULL)
		{
			*errorNum = notFound(argv[0], *errorNum, args[0]);
		}
		else
		{
			executeTheExecCommand(filePath, args, envp);
		}
	}
}
