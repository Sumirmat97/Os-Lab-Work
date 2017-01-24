#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void removeEndline(char *str)
{
	int i;
	for(i=0;i<strlen(str);i++)
	{
		if(str[i] == '\n')
			str[i] = '\0';
	}
}

void execute(char *command[],int flag,int isPipe)
{
	int i;
	
	pid_t firstPid,secondPid;
	static char *subCommand[10];
	//int saved_stdout = dup(STDOUT_FILENO);

	if(command[0] == (char *)NULL)	//if empty input then return 
	{
		printf("Command not found\n");
		return;
	}

	if(flag == 2 && !isPipe)	//if the pipeline operator comes the first time copy the first command in to subCommand 
	{
		for(i=0; command[i]!=(char *)NULL; i++)
		{
			subCommand[i] = command[i];
		}
		subCommand[i] = (char *)NULL;
		return;

	}
	else if(isPipe)			//if pipeline is set the execute this 
	{
		int fd[2];
		pipe(fd);

		firstPid = fork();

		if(firstPid < 0)
		{
			printf("*** ERROR: forking child process failed\n");	//if fork() fails
			return;
		}
						
		else if(firstPid == 0)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			
			if(!strcmp(subCommand[0],"cd"))	//if cd command is given in input
			{
				if(subCommand[1] != NULL)
				{
					if(chdir(subCommand[1]) == -1) // if directory does not exists
					{
						printf("No such directory found\n");
					}
				}
				else			//if no path is given after the cd command change directory to home
				{
					chdir("/home");	
				}
			}
			else			
				if(execvp(subCommand[0],subCommand) < 0)  
				{
					printf("command not found\n");
				}
			exit(0);
	
		}	

		else
		{
		
			secondPid = fork();
			if(secondPid < 0)
			{
				printf("*** ERROR: forking child process failed\n");	//if fork() fails
				return;
			}

			if(secondPid==0)
			{
				dup2(fd[0], STDIN_FILENO);
				close(fd[1]);

				if(!strcmp(command[0],"cd"))	//if cd command is given in input
				{
					if(command[1] != NULL)
					{
						if(chdir(command[1]) == -1) // if directory does not exists
						{
							printf("No such directory found\n");
						}
					}
					else			//if no path is given after the cd command change directory to home
					{
						chdir("/home");	
					}

				}
				else
					if(execvp(command[0],command) < 0)  
					{
						printf("command not found\n");
					}
				exit(0);
			}
			else
			{
				if(strcmp(command[0],"exit")==0)
				{
					kill(secondPid, SIGKILL);
					printf("\n**Exiting ListenerShell**\n");
					exit(0);
				}
				if(flag == 0)	//Wait only if the process is foreground 
				{	
					wait(NULL);
				}
				else if(flag == 1)
				{
					printf("%d\n",secondPid);
				}
			}
		}
		close(fd[0]);
		close(fd[1]);
		wait(NULL);
	}
	else			//if pipeline is not present in the input
	{
		if(strcmp(command[0],"exit")==0)
		{
			printf("\n**Exiting ListenerShell**\n");
			exit(0);
		}

		if(!strcmp(command[0],"cd"))	//if cd command is given in input
		{
			if(command[1] != NULL)
			{
				if(chdir(command[1]) == -1) // if directory does not exists
				{
					printf("No such directory found\n");
				}
			}
			else			//if no path is given after the cd command change directory to home
			{
				chdir("/home");	
			}
			return;

		}
	
		pid_t pid = fork();
		if(pid < 0)
		{
			printf("*** ERROR: forking child process failed\n");	//if fork() fails
			return;
		}
		else if(!pid)
		{		
			//for child process
			if(execvp(command[0],command) < 0)  
			{
				printf("command not found\n");
			}
			exit(0);
		}
		else
		{
			
			//for parent process
			if(strcmp(command[0],"exit")==0)
			{
				kill(pid, SIGKILL);
				printf("\n**Exiting ListenerShell**\n");							
				exit(0);
			}
			if(flag == 0)	//Wait only if the process is foreground 
			{	
				waitpid(pid,NULL,0);
			}
			else if(flag==1)
			{
				printf("%d\n",pid);
			}
		}	
	}
}

int main()
{
	char *input = NULL;
	char *token;
	size_t size;
	int counter=0,flag=0,i; //flag 0. => foreground, 1. => background
	char *path = NULL;			
	char *args[10];
	int isPipe = 0; 	//to tell if pipeline is present or not
	
	do
	{
		
		for(i=0;i<10;i++)		//initialising each of the strings to null
			args[i] = (char *)NULL;
	
		printf("Sumir@ListenerShell:%s$ ",getcwd(path,size));

		getline(&input,&size,stdin);
		
		if(feof(stdin)) break;	//for ctrl+D 
		if(!strcmp(input,"exit\n")) break; //if exit is given in input
		if(!strcmp(input,"\n")) continue; //if '\n' is given in input

		removeEndline(input);

		token = strtok(input," ");
		
		while(token!=NULL)
		{ 
			args[counter++] = token;			
			if(!strcmp(token,"&"))
			{	
				flag = 1;				//if & is found put null in args and execute the command till there
				args[--counter] = (char *)NULL;	
				execute(args,flag,isPipe);
				
				for(i=0;i<=counter;i++)			//re initialise the array and the counter
					args[i] = (char *)NULL;
				counter=0;
				flag = 0;		
			}	
			else if(!strcmp(token,"&&"))			//if && comes execute the commands differently. 
			{	
				flag = 0;			
				args[--counter] = (char *)NULL;		
				execute(args,flag,isPipe);
				
				for(i=0;i<=counter;i++)			//re initialise the array and the counter
					args[i] = (char *)NULL;	
				counter = 0;		
			}
			else if(!strcmp(token,"|"))
			{
				flag = 2;
				args[--counter] = (char *)NULL;
				execute(args,flag,isPipe);

				isPipe = 1;										
				for(i=0;i<=counter;i++)			//re initialise the array and the counter
					args[i] = (char *)NULL;	
				counter = 0;
				flag = 0;		
								
			}
			token = strtok(NULL," ");
					
		}	
		
		args[counter] = (char *)NULL;		//explicitly put a NULL in the last position of args so that execvp can work
		flag = 0;
		if(token == NULL && counter>0)		// if end of input was reached and pipeline operator not present in the input and first index of args != NULL 
		{
			execute(args,flag,isPipe);
		}			

		counter = 0;	
		input = NULL;
		flag = 0;
		isPipe = 0;
	
	}while(1);
	
	printf("\n**Exiting ListenerShell**\n");
	
	return 0;  
}
