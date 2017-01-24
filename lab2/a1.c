#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>
#define SIZE 80
#define READ_END 0
#define WRITE_END 1

int executeCommand(char *token[SIZE],int endOfCommands,char mode)
{
	static char *tokenAux[SIZE];
	int DONT_WAIT=0,PIPE_ON=0,i=0;
	FILE *fin,*fout=fopen("out","w");
	//printf("%d\n",i);
	int saved_stdout = dup(STDOUT_FILENO);
	if(token[0]==NULL)
	return 1;
	switch(mode)
	{
		case '&':
			DONT_WAIT=1;
			break;
		case '2':
			PIPE_ON=1;
		case '|':
			do
			{
				tokenAux[i]=token[i];
			}while(token[i++]);
			return 1;
			break;
		case '1':
			DONT_WAIT=1;
		case '0':
			PIPE_ON=1;
			break;
			
	}
	if(PIPE_ON)
	{
		int pid,fd[2];
		pipe(fd);
		pid=fork();
		if(pid==0)
		{
		    //printf("i'm the child used for ls \n");
		    dup2(fd[WRITE_END], STDOUT_FILENO);
		    close(fd[READ_END]);
		    if(strcmp(tokenAux[0],"cd")==0)
			{
				if(tokenAux[1]!=NULL&&tokenAux[2]==NULL)
				{
					if(chdir(tokenAux[1]))
					{
						printf("error in changing directory\n");
					}
					//return 0;
				}
				else
				{
					printf("cd <path> is the format\n");
				}
			}
			else
				if(execvp(tokenAux[0],tokenAux)<0)
					printf("%s: command not found\n",tokenAux[0]);
			exit(0);
		}
		else
		{ 
		    pid=fork();

		    if(pid==0)
		    {
		        //printf("i'm in the second child, which will be used to run grep\n");
		        dup2(fd[READ_END], STDIN_FILENO);
		        close(fd[WRITE_END]);
		        if(strcmp(token[0],"cd")==0)
				{
					if(token[1]!=NULL&&token[2]==NULL)
					{
						if(chdir(token[1]))
						{
							printf("error in changing directory\n");
						}
						//return 0;
					}
					else
					{
						printf("cd <path> is the format\n");
					}
				}
				else
					if(execvp(token[0],token)<0)
						printf("%s: command not found\n",token[0]);
				exit(0);
		    }
		    else
		    {
		    		if(strcmp(token[0],"exit")==0)
				{
					kill(pid, SIGKILL);
					printf("rsh closing... havde a nice day\n");
					return 0;
				}
				if(!DONT_WAIT)
				{
					wait(NULL);
					return 1;
				}
				else
				{
					printf("pid %d running\n",pid);
					return 1;
				}
		    }
		}
	}
	else
	{
		int pid=fork();
		if(pid==0)
		{
			//printf("%s\n",token[0]);
			if(strcmp(token[0],"exit")==0)
			{
				//printf("rsh closing... have a nice day\n");
				return 0;
			}
			else if(strcmp(token[0],"cd")==0)
			{
				if(token[1]!=NULL&&token[2]==NULL)
				{
					if(chdir(token[1]))
					{
						printf("error in changing directory\n");
					}
					//return 0;
				}
				else
				{
					printf("cd <path> is the format\n");
				}
			}
			else
				if(execvp(token[0],token)<0)
					printf("%s: command not found\n",token[0]);
			exit(0);
		}
		else
		{
			if(strcmp(token[0],"exit")==0)
			{
				kill(pid, SIGKILL);
				printf("rsh closing... havde a nice day\n");
				return 0;
			}
			if(!DONT_WAIT)
			{
				waitpid(pid,NULL,0);
			}
			else
			{
				printf("pid %d running\n",pid);
				return 1;
			}
		}
	}
	//printf("adsf\n");
	//dup2(saved_stdout, STDOUT_FILENO);
	//fclose(fout);
	//printf("adsf\n");
	return 1;
}

int main(int argv,char *args[])
{
	char buffer[SIZE],*token[SIZE],*file;
	int PIPE=0;
	while(1)
	{
		printf("user/rsh$ ");
		//if(!scanf(" %80[^\n]s",buffer))continue;
		gets(buffer,SIZE);
		if(feof(stdin))
		{
			strcpy(buffer,"exit ");
			printf("exit\n");
		}
		if(buffer[0]==0)continue;
		token[0]=strtok(buffer," ");
		int i=1,j=0;
		do
		{
			token[i]=strtok(NULL," ");
			if(token[i]==NULL)
			{
				if(PIPE)
				{
					if(executeCommand(token+j,i,'0')==0)
					{
						return 0;
					}
				}
				else if(executeCommand(token+j,i,' ')==0)
				{
					return 0;
				}
				j=i+1;
			}
			else if(strcmp(token[i],"&")==0)
			{
				token[i]=NULL;
				if(PIPE)
				{
					if(executeCommand(token+j,i,'1')==0)
					{
						return 0;
					}
				}
				else if(executeCommand(token+j,i,'&')==0)
				{
					return 0;
				}
				token[i]="&";
				j=i+1;
			}
			else if(strcmp(token[i],"|")==0)
			{
				token[i]=NULL;
				if(PIPE)
				{
					if(executeCommand(token+j,i,'2')==0)
					{
						return 0;
					}
				}
				else if(executeCommand(token+j,i,'|')==0)
				{
					return 0;
				}
				token[i]="|";
				PIPE=1;
				j=i+1;
			}
		}while(token[i++]!=NULL);
	} 
	return 0;
}
