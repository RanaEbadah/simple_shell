#ifndef SHELL_H
#define SHELL_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<limits.h>
#include<fcntl.h>
#include<limits.h>
#include<errno.h>
#include <dirent.h>
#include <stdint.h>


/*string functions*/
int _strlen(char *str);
char *concat_string(char *strDest, char *strSrc);
char *_strcpy(char *dest, char *src);
int _strcmp(char *str1, char *str2);
int _strncmp(char *str1, char *str2, int n);


/*shell.c functions*/
char **handleCommandLine(char *command);
char *getPathFromEnv(char *env[]);
char *isExec(char *path, char *fileName);
int CommandIsSpace(char *command);
int commandIsSpaceOrEnter(char *strCommand);

/*functions.c*/
int printString(char *str);
char *_strdup(char *str);
char *excludeUnNeedTerminatot(char *str);
void printInteger(int num);


/*main.c*/

void exitTheShell(char *line, int exitStatus);
int notFound(char *shellName, int errorNum, char *commandName);
int executeTheExecCommand(char *filePath, char **args, char *envp[]);
void executeCommand(char *line, char *path, char **args, char **envp,
char **argv, int *errorNum);
#endif /*SHELL_H */
