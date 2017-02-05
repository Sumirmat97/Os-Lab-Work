#include<stdio.h>
#include<unistd.h>
#include<sys/syscall.h>
#include<linux/kernel.h>

int main()
{	
	long retValue = syscall(548);
 	printf("The value returned by th syscall 'mySysCall' is %ld\n",retValue);
	return 0;
}
