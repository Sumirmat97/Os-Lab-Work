
Q1.How many levels of paging does linux use? How did you find this out? 

Ans1. Linux uses 4 levels of paging. these levels are named as PGD, PMD, PTE, Page table entry.

	  I found this from various websites, some of them are:

			1. https://0xax.gitbooks.io/linux-insides/content/Theory/Paging.html
			2. Stack overflow: http://stackoverflow.com/questions/12557267/linux-kernel-memory-management-paging-levels
			3. https://lwn.net/Articles/106177/

Q2.Find out process memory layout for your own program.

Ans2. The code used was:
	  This on run displays the pid of the proocess which runs it.
	  Also pauses the program in between since I have used getchar() function.
	  
			#include <stdio.h> 
			#include <stdlib.h> 
			#include <unistd.h> 
			#include <sys/types.h> 

			extern int a,i,j,k;

			int main () {

				char * addr;
				printf("Welcome to per thread arena example::%d\n", getpid());
				printf("Before malloc in the main thread\n");
				getchar();
				addr = (char *) malloc(1000);
				printf("After malloc and before free in main thread\n");
				free(addr);
				printf("After free in main thread\n");
				

				return 0;

			}

	To see the process memory layout pause the run the proggram and pause it using Ctrl + Z.
	And run command cat /proc/$pid/maps ($pid is the process id of the process)

	The output it gave was:
	
		00400000-00401000 r-xp 00000000 08:07 1739374                            /home/sumir/Desktop/2015KUCP1017OSLAB/lab11/memory_layout
		00600000-00601000 r--p 00000000 08:07 1739374                            /home/sumir/Desktop/2015KUCP1017OSLAB/lab11/memory_layout
		00601000-00602000 rw-p 00001000 08:07 1739374                            /home/sumir/Desktop/2015KUCP1017OSLAB/lab11/memory_layout
		00d18000-00d39000 rw-p 00000000 00:00 0                                  [heap]
		7faee0227000-7faee03e6000 r-xp 00000000 08:07 1718267                    /lib/x86_64-linux-gnu/libc-2.23.so
		7faee03e6000-7faee05e6000 ---p 001bf000 08:07 1718267                    /lib/x86_64-linux-gnu/libc-2.23.so
		7faee05e6000-7faee05ea000 r--p 001bf000 08:07 1718267                    /lib/x86_64-linux-gnu/libc-2.23.so
		7faee05ea000-7faee05ec000 rw-p 001c3000 08:07 1718267                    /lib/x86_64-linux-gnu/libc-2.23.so
		7faee05ec000-7faee05f0000 rw-p 00000000 00:00 0 
		7faee05f0000-7faee0608000 r-xp 00000000 08:07 1718278                    /lib/x86_64-linux-gnu/libpthread-2.23.so
		7faee0608000-7faee0807000 ---p 00018000 08:07 1718278                    /lib/x86_64-linux-gnu/libpthread-2.23.so
		7faee0807000-7faee0808000 r--p 00017000 08:07 1718278                    /lib/x86_64-linux-gnu/libpthread-2.23.so
		7faee0808000-7faee0809000 rw-p 00018000 08:07 1718278                    /lib/x86_64-linux-gnu/libpthread-2.23.so
		7faee0809000-7faee080d000 rw-p 00000000 00:00 0 
		7faee080d000-7faee0833000 r-xp 00000000 08:07 1718268                    /lib/x86_64-linux-gnu/ld-2.23.so
		7faee0a0d000-7faee0a10000 rw-p 00000000 00:00 0 
		7faee0a30000-7faee0a32000 rw-p 00000000 00:00 0 
		7faee0a32000-7faee0a33000 r--p 00025000 08:07 1718268                    /lib/x86_64-linux-gnu/ld-2.23.so
		7faee0a33000-7faee0a34000 rw-p 00026000 08:07 1718268                    /lib/x86_64-linux-gnu/ld-2.23.so
		7faee0a34000-7faee0a35000 rw-p 00000000 00:00 0 
		7fff29b62000-7fff29b83000 rw-p 00000000 00:00 0                          [stack]
		7fff29bf7000-7fff29bf9000 r--p 00000000 00:00 0                          [vvar]
		7fff29bf9000-7fff29bfb000 r-xp 00000000 00:00 0                          [vdso]
		ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
		
	Each row in /proc/$PID/maps describes a region of contiguous virtual memory in a process. 
	Each row has the following fields:

    1. address - starting and ending address in the region's process address space
    2. perms - permissions
    3. offset - if the region was mapped by a file using mmap, this is the offset in the file where the mapping begins
    4. dev - if the region was mapped from a file, this is major and minor device number in hex where the file lives, 
		the major number points to a device driver, and the minor number is interpreted by the device driver, or the minor 
		number is the specific device for a device driver, like multiple floppy drives
    5. inode - if the region was mapped from a file, this is the file number
    6. pathname - if the region was mapped from a file, this is the name of the file, there are special regions with names like
		[heap], [stack] and [vdso], [vdso] stands for virtual dynamic shared object, its used by system calls to switch to kernel mode.


	Details of the output:

	1.  The First line in the output is the code segment it starts from the reallocatable address 400000 and expands upto 401000. (This is 4 Kb )
	
	2.	The Second line in the output is the initialised data segment it starts from the reallocatable address 600000 and expands upto 601000. (This is 4 Kb )
	
	3.	The Third line in the output is the uninitialised data segment (also known as BSS) it starts from the reallocatable address 601000 and expands upto 602000. (This is 4 Kb )
	
	4.	So each of these occupy one code one pagesize. (as given by getconf PAGESIZE)

	5.	The Fourth line in output is the heap segment it starts from rellocatable address 00d18000 and expands upto 00d39000. (This is 132 Kb)

	6.	After heap are the libraries that were included in the program.

	7.	Some regions don't have any file path or special names in the pathname field, these are anonymous regions. 
		Anonymous regions are created by mmap, but are not attached to any file, they are used for miscellaneous things like shared memory, buffers not on the heap,
		and the pthread library uses anonymous mapped regions as stacks for new threads.
		 
	8.	After these is the stack segment it starts from logical address 7fff29b62000 and expands upto 7fff29b83000. (This is 132 Kb)
		 
	9.	The included libraries come in between the stack and the heap.

	10. Also if the same program is run on different terminal then the code and the data (initialised and uninitialised) segment get the same address but others get different addresses.
