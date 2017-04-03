/* fileCreate.c

   Simple program to test whether running a user program works.
 	
   Just invokes a system call that opens a file. */

#include <syscall.h>

int
main (void)
{

	const char * a = "SUMIR.txt";
	int fd = open(a);
  
  /* not reached */
}
