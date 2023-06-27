#include "shell.h"

/**
*handleCommandLine - get args fromCommand
*@command: the comand
*Return: array of arguments
*/
char **handleCommandLine(char *command)
{
	char **args;
	char *token;
	int tokenCount = 0;

	if (command == NULL)
	return (NULL);

	args = malloc(30 * sizeof(char *));
	if (args == NULL)
	{
		free(args);
		return (NULL);
	}

	token = strtok(command, " ");

	while ((token != NULL) && tokenCount < 50)
	{
		if (commandIsSpaceOrEnter(token) != 1)
		{
			args[tokenCount] = token;
			tokenCount++;
		}
		token = strtok(NULL, " ");
	}

	args[tokenCount] = NULL;

	return (args);
}


/**
*getPathFromEnv - extract the PATH from main env args
*@env: the main env args.
*Return: 1 or 0
*/
char *getPathFromEnv(char *env[])
{
	int i, same;
	char *path = NULL;

	for (i = 0; env[i] != NULL; i++)
	{
		same = _strncmp(env[i], "PATH=", 5);
		if (same == 0)
		{
			path = env[i] + 5;
			break;
		}
	}
	return (path);
}

/**
*isExec - check if the command is executable or not
*(found on the PATH or not)
*@fileName: the file name to be checked
*@path: the PATH will be here.
*Return: the path of the file
*/
char *isExec(char *path, char *fileName)
{
	char *token, *filePath;
	char *path_copy = NULL;

	if ((path == NULL) || (fileName == NULL))
	return (NULL);

	if (fileName[0] == '/')
	{
		if (access(fileName, X_OK) == 0)
		return (fileName);
		else
		return (NULL);
	}
	/*we will make a copy from path to avoid changing the value of path itself*/
	path_copy = _strdup(path);
	if (path_copy == NULL)
	{
		free(path_copy);
		return (NULL);
	}
	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		if (token[_strlen(token) - 1] != '/')
		filePath = concat_string("/", fileName);
		else
		filePath = fileName;
		token = concat_string(token, filePath);
		if (access(token, F_OK) == 0)
		{
			free(path_copy);
			return (token);
		}
		token = strtok(NULL, ":");
	}
		free(path_copy);
		return (NULL);
	}


/**
*CommandIsSpace - check if the command is just spaces
*@command: The command to be checked
*Return: if pace 1, if no 0
*/
int CommandIsSpace(char *command)
{
	int i = 0, isSpace = 0;

	for (i = 0; i < _strlen(command); i++)
	{
		if (command[i] == ' ')
		isSpace = 1;
		else
		{
			isSpace = 0;
			break;
		}
	}

	return (isSpace);
}

/**
*commandIsSpaceOrEnter - check if the command is just spaces & enters
*@strCommand: The command to be checked
*Return: if pace 1, if no 0
*/
int commandIsSpaceOrEnter(char *strCommand)
{
	int i = 0, yes = 0;

	if (strCommand == NULL)
	return (-1);

	while (strCommand[i] != '\0')
	{
		if (strCommand[i] == ' ' || strCommand[i] == '\t' ||
		strCommand[i] == '\n' || strCommand[i] == '\v' ||
		strCommand[i] == '\f' || strCommand[i] == '\r')
		yes = 1;
		else
		{
			yes = 0;
			return (yes);
		}
		i++;
	}

	return (yes);
}
