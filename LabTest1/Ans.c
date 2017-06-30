#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int test_and_set(int* lock)
{
	
	int initial = *lock;
	if(*lock)
		*lock = 0;
	else *lock = 1;
	return initial;
}

int main()
{
	int lock = 0; 
		
	pid_t pid = fork();
		
	if(pid < 0)
	{
		printf("*** ERROR: forking child process failed\n");	//if fork() fails
		return 1;
	}
	
	else if(!pid)
	{	
		//for child process which is the consumer
		do{
			
			while(test_and_set(&lock) == 1);
							
			printf("child locked");	
			
			printf("%d\n",lock);
			
		}while(1);
	}
	else
	{
		
		//for parent process which is the producer
		do{
				while(test_and_set(&lock) == 0);
				
				printf("parent locked");
				
				printf("%d\n",lock);
				
			}while(1);
	}	
	
	return 0;
}
