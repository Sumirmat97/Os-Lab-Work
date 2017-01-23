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

void execute(char *command[],int flag)
{

	int waitValue;

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
	{	//for parent process
		if(flag == 0)	//Wait only if the process is foreground 
		{	
			waitpid(pid,NULL,0);
		}
		else
		{
			printf("%d\n",pid);
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
				printf("%d ",flag);	
				execute(args,flag);
				
				for(i=0;i<=counter;i++)			//re initialise the array and the counter
					args[i] = (char *)NULL;
				counter=0;
				flag = 0;
				printf("%d  ",flag);				
			}	
			else if(!strcmp(token,"&&"))			//if && comes execute the commands differently. 
			{	
				flag = 0;			
				args[--counter] = (char *)NULL;		
				execute(args,flag);
				
				for(i=0;i<=counter;i++)			//re initialise the array and the counter
					args[i] = (char *)NULL;	
				counter = 0;		
			}
			token = strtok(NULL," ");
					
		}	
		
		args[counter] = (char *)NULL;
		flag = 0;
		if(counter > 0)						//check if args has non null value in the first index itself 
			execute(args,flag);			

		counter = 0;	
		input = NULL;
		flag = 0;
	
	}while(1);
	
	printf("\n**Exiting ListenerShell**\n");
	
	return 0;  
}
