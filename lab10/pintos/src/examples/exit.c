/* exit.c

   Simple program to test whether running a user program works.
 	
   Just invokes a system call that exits a process. */

#include <syscall.h>

int
main (void)
{

  exit(1);
  /* not reached */
}
