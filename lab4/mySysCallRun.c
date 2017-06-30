#include<stdio.h>
#include<unistd.h>
#include<sys/syscall.h>
#include<linux/kernel.h>

int main()
{	
	long retValue = syscall(548); // this works
	//long retValue = mySysCall(); this doesn't work
	
 	printf("The value returned by th syscall 'mySysCall' is %ld\n",retValue);
	return 0;
}
