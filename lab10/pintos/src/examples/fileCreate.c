/* fileCreate.c

   Simple program to test whether running a user program works.
 	
   Just invokes a system call that creates a file, opens it and closes it. */

#include <syscall.h>

int
main (void)
{

   const char * a = "SUMIR.txt";
  create(a,10);
  
  /* not reached */
}
