#include "shell.h"

/**
*handleCommandLine - get args fromCommand
*@command: the comand
*Return: array of arguments
*/
char** handleCommandLine(char *command)
{
    char **args;
    char *token;
    int tokenCount = 0;

    if (command == NULL)
    return (NULL);
    
    args = malloc (30 * sizeof(char*));
    if(args == NULL)
    return (NULL);

    token = strtok(command, " ");

    while ((token != NULL) && tokenCount < 50)
    {
        if (commandIsSpaceOrEnter(token) != 1)
        {
            /*printf("The token is %s\n", token);*/
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
*@path: the PATH will be here.
*Return: 1 or 0
*/
char* getPathFromEnv(char *env[])
{
    int i, same;
    char *path = NULL;

    for (i = 0; env[i] != NULL; i++)
    {
        same = _strncmp(env[i], "PATH=", 5);
        if (same == 0)
        {
            path = env[i] + 5;
            break;;
        }
    }
    return (path);
}

/**
*isExec - check if the command is executable or not
*(found on the PATH or not)
*@str: the string that we will get it's length.
*Return: the lenght of the string / -1 if the sting is null
*/
char* isExec(char *path, char *fileName)
{
    char *token, *filePath;
    char *path_copy = NULL;

    /*printf("filename is %s\n", fileName);*/
    if ((path == NULL) || (fileName == NULL))
    return (NULL);
    
    /*we will make a copy from path to avoid changing the value of path itself*/
    path_copy = _strdup(path);
    if(path_copy == NULL)
    return (NULL);
    
    token = strtok(path_copy, ":");
  
    while (token != NULL)
    {
        if (token[_strlen(token) - 1] != '/')
        filePath = concat_string("/", fileName);
        else
        filePath = fileName;
       
        token = concat_string(token, filePath);
        /*printf("---------------------------------------------------------------");*/
        /*printf("tokennn is %s\n", token);*/
        /*printf("the length of token is %d\n", _strlen(token));
        printf("_strlen(token) - 1 = %d\n", _strlen(token) - 1);*/
        token[_strlen(token) - 1] = '\0';
        
        /*printf("tokennnnnnn is %s\n", token);*/
        if(access(token, F_OK) == 0)
        {
            return (token);
        }
      
        token = strtok(NULL, ":");
    }
    return (NULL);
      
    }
    

/**
*CommandIsSpace - check if the command is just spaces
*@comman: The command to be checked
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

    return(isSpace);
}


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
