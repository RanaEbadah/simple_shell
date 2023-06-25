#include "shell.h"

int main(__attribute__((unused)) int argc,__attribute__((unused)) char *argv[], char *envp[])
{
    char *line = NULL, *path, *filePath, **args, **envpCopy = NULL;
    size_t len;
    pid_t pid;
    int executed;
    int status;
    int readed, errorNum = 1;
    
    envpCopy = envp;
    path = getPathFromEnv(envpCopy);/*get the path*/

    while(1)
    {
        printf("$ ");
        readed = getline(&line, &len, stdin);
        
        if (readed == -1) /*EOF handling*/
        {
            printf("\n");
            free(line);
            exit(0);
        }
        if (commandIsSpaceOrEnter(line) == 1)
        continue;/*if the input is enter or space continue*/
       
        args = handleCommandLine(line); /*parse the line to command and arguments*/
        
        if((args == NULL) || (path == NULL))
        return(1);
        
        if(_strcmp(args[0], "exit") == 0)
        {
            /*handle exit code*/
        }
        else
        {
            filePath = isExec(path, args[0]);
            
            if(filePath == NULL)
            {
                printf("%s: %d: %s: not found\n", argv[0], errorNum, args[0]);
                errorNum++;
                continue;
            }
            else
            {
                /*we will execute the command*/
                pid = fork();
                
                if(pid == -1) return (1);
                else if (pid == 0)
                {
                    executed = execve(filePath, args, envp);
                    if(executed == -1)
                    return (1);
                }
                else
                {
                    /*it is a parent*/
                    wait(&status);
                }
            }
        }  
    } 
    return (0);
}
