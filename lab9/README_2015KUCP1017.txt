
Ans 1.

	A.malloc() 
		malloc is used to dynamicaly allocate memory of a specified size at the time of execution of a program.It return a pointer to the allocated memory.
		The memory is not initialised i.e. it may have garbage value. It can return NULL if we try too allocate 0 Bytes.
		
		Syntax:
		
		 void *realloc(size_t size)
			It allocates size Bytes of memory and returns a pointer which can be type casted to appropriate pointer type.
			
		eg. Usage in program:	
		
			int *a  = (int *)malloc(sizeof(int));
			
			Here the pointer a is allocated 4 Bytes (i.e. the size of int) during the execution of this statement.
				
		Continous memory is allocated by using malloc
		
		
	B.calloc()
		The  calloc() function is used to dynamically allocate memory for an array of N elements of M bytes each at the time of execution of the program. 
		It returns a pointer to the begining of the allocated memory. The memory is initialised to zero (or in case of char to NULL). 
		calloc() accepts two arguments. First the number of elements(N) and second the size of each element(M). 
		If N or M is 0, then calloc() returns either NULL, or a unique pointer value.
		
		Syntax :
		
		void *calloc(size_t nitems, size_t size)
			nitems  This is the number of elements to be allocated.	
			size  This is the size of each of the elements.

		eg. Usage in program
		
			#define LARGE 100
			int *arr = (int *)calloc(LARGE,sizeof(int));
			Here 100 blocks of memory each of size 4 Bytes are allocated and arr points to the begining of the arr.
			
			Continous memory is allocated by using calloc
		
		The difference between malloc() and calloc() is that
		1. malloc() allocates single block of memory whereas calloc() allocates multiple blocks of memory each of same size 
		2. calloc() sets all bytes to zero.
		
		
	C.realloc()
		The  realloc() function changes the size of the memory block pointed to by ptr to size bytes. 
		The contents will be unchanged in the range from the start of the region up to the minimum of the old and new sizes.
		If the new size is larger than the old size, the added memory will not be initialized.
		If  ptr  is  NULL,  then  the call is equivalent to malloc(size). 
		If size is equal to zero, and ptr is not NULL, then the call is equivalent to making size 0 that is freeing all the allocated memory.
		
		Syntax:
		
		void *realloc(void *ptr, size_t size)
			ptr: This is the pointer to a memory block previously allocated with malloc, calloc and is to to be reallocated.
			If this is NULL, a new block is allocated and a pointer to it is returned by the function.

			size:  This is the new size for the memory block, in bytes.
			If it is 0 and ptr points to an existing block of memory, the memory block pointed by ptr is deallocated and a NULL pointer is returned.

		
		eg. Usage in program
			#define LARGE 90
			#define SMALL 10
			
			int *arr = (int *)calloc(SMALL,sizeof(int));
			
			arr = (int *)realloc(arr,LARGE);
			
		Precautions:
			If continous memory equal to the new size is not present the pointer returned may be a pointer to another location where continous memory is availablle..
			That is the pointer may point to another location different from the previously allocated physical address. This may result in the loss of old values. 
			
			
	D.free()
		The free() function frees (deallocates) the memory space pointed to by ptr, which must have been returned by a previous call to malloc(), calloc(), or realloc().
		If ptr is NULL, no operation is performed.
		If free(ptr) has already been called before, undefined behavior occurs. 
			
		Syntax: 	
			void free(void *ptr)
			ptr -- This is the pointer to a memory block previously allocated with malloc, calloc or realloc to be deallocated.
			
		eg. Usage in program
			
			int *a = (int *)malloc(sizeof(int));
			
			/* Some computation with a */
			
			free(a);
			
			
		Precaution:
			free should not be used to deallocate a pointer which was already deallocated.
			
	E.alloca()
		The  alloca() function allocates size Bytes of space in the stack segment of the caller.
		This temporary space is automatically  freed  when the function that called alloca() returns to its caller.

		The header file for alloca() is "alloca.h"

		Syntax:
			void *alloca(size_t size);
			
			size is the number of Bytes of memory you want to allocate. 


		eg. Usage in program
				
			#define LARGE 100
			char *str = (char *) alloca(LARGE);
			  
		Precautions:
		If the allocation causes stack overflow, program behavior is undefined. Therefore care should be taken while using alloca();

	
	F.longjmp()
	
		Syntax:
			void longjmp(jmp_buf env, int val);
				env − This is the object of type jmp_buf containing information to restore the environment at the setjmp's calling point.
				value − This is the value to which the setjmp expression evaluates.		

		The header file for longjmp() is "setjmp.h"
		
		longjmp() restores  the  environment saved by the last call of setjmp(3) with the corresponding env argument.  After longjmp() is completed, 
		program execution  continues  as  if  the corresponding call of setjmp(3) had just returned the value val.
		longjmp() cannot cause 0 to be  returned.   
		
		
		eg. Usage in program
			
			int main()
			{
			   int val;
			   jmp_buf env_buffer;

			   val = setjmp( env_buffer );
			   
			   if( val != 0 ) 
			   {
				  printf("Returned from a longjmp() with value = %s\n", val);
				  exit(0);
			   }
			   printf("Jump function call\n");
			   jmpfunction( env_buffer );
			   
			   return(0);
			}

			void jmpfunction(jmp_buf env_buf)
			{
			   longjmp(env_buf, "tutorialspoint.com");
			}
			
			
	G.brk()
	
		Syntax :

			int brk(void *addr);
			
		brk() change the location of the program break, which defines the end of the process's data segment (i.e., the program break is the first 
		location after the end of the uninitialized data segment).  Increasing the program break has the effect of allocating memory to the process; 
		decreasing the break deallocates memory.	
		brk() sets the end of the data segment to the value specified by addr, when the system has enough memory, and the process does not exceed its maximum data size.
		
		The header file for alloca() is "unistd.h"
		
	H.mmap()
	
		Syntax:
			 void *mmap(void *addr, size_t length, int prot, int flags,int fd, off_t offset);
                 
        map files or devices into memory.
                  
		mmap() creates a new mapping in the virtual address space of the calling process. The starting address for the new mapping is specified in addr.
		The length argument specifies the length of the mapping.

		If addr is NULL, then the kernel chooses the address at which to create the mapping; this is the most portable method of creating a new mapping.
		If addr is not NULL, on Linux, the mapping will be created at a nearby page boundary.
		The address of the new mapping is returned as the result of the call.
		
		The header file for alloca() is "sys/mman.h"
	
	J.munmap()

		Syntax:			
			int munmap(void *addr, size_t length);

		unmap files or devices into memory.

		The munmap() system call deletes the mappings for the specified address range, and causes further references to addresses within the 
		range to generate invalid memory references.  The region is also automatically unmapped when the process is terminated.  On the other hand,
		closing the file descriptor does not unmap the region.
			
		The header file for alloca() is "sys/mman.h"
	
	
	Precaution to avoid memory corruption:
		
	To avoid corruption in multithreaded applications, mutexes are used internally to protect the memory-management data structures employed by these functions.
	In a multithreaded application in which threads simultaneously allocate and free memory, there could be contention for these mutexes.
	To scalably handle memory allocation in multithreaded applications, glibc creates additional memory allocation arenas if mutex contention is detected.
	Each arena is a large region of memory that is internally allocated by the system (using brk(2) or mmap(2)), and managed with its own mutexes.


Ans2.


	Program to show illustrate memory leak
	
	#include<stdio.h>
    #include<stdlib.h>
    
    int main()
    {
		int *p;
		while(1)
		{
			p = (int *) malloc(10000000000 * sizeof(int));
			if(p == NULL) // if no memory is available.
			{
				printf("No avilable memory\n");
				break;
			}
			else 
			{
				printf("Memory Allocated\n");
			}
		}
		
	}
	
	This program will allocate memory for time. But since it is an infinte loop, after some time all availlable memory will get exhausted as we are not freeing any memory.
	The situation where memory, which is no more in use, is not freed using free() causes decrease in the available free memory. This situation is called memory leak.

	In simple terms, memory leak occurs when programmers create a memory in heap and forget to delete it.This is not deallocated automatically and keeps on occuping memory.
	

	Fixing Memory leak: 
	This situation can be fixed if the alloated memory is freed using the function free() and made available for the use of other processes.

 
	The best practices that should be followed while using memory management related functions:
	
		(i) Always check the returned pointer from malloc for NULL.
		(ii) Set a pointer to NULL after freeing it.
		(iii) Try to malloc and free a chunk of memory within the same scope if possible.
		(iv) Never work with the allocated pointer. Always use a copy.

			  For example: 
				int *p = (int*) malloc( sizeof(int) * n );
				int *p_copy = p;
				// do your stuff with p_copy, not with p_allocated
			
				free (p_allocated)

			 Thus we are safe from accidentally changing the pointer and returning the wrong address over to free. 

		(v) Be careful when using realloc(). Do not use the same pointer for input & output parameters.
		(vi) Can use tools such as "valgrind" to check for memory leaks. It will show all the memory that are not freed on termination of the program.
		(vii) Do not allocate and deallocate memory in a loop as this may slow down the program and may sometime cause security malfunctions.
		
Ans3.

	The code to display the addresses of the different segments is:
	
		#include<stdio.h>
		#include<stdlib.h>

		int a;
		void display(int n)
		{
			printf("address of stack = %p\n", (void *)&n);
		}

		int main()
		{
				int i,*ptr;
				ptr = (int *) malloc(sizeof(int));
				printf("address of data segment = %p\n",(void *)&a);
				printf("address of Heap = %p\n", (void *)&ptr);
				printf("address of code segment = %p\n",(void *)&main);
				display(10);
				return 0;
		}

	The outputs of different terminals are in the sreenshots Terminal1.png and Terminal2.png
	The addresses of stack and heap segments change when executed on differnt terminals but the address of data and code segments are the same.
	
	
Ans4.

	#include<stdio.h>

	int main(void)
	{
		int x = 2;
		int *ptr = &x;
		printf("Hello Os!\n");
		return 0;
	}

	To run in debugger command was
	gcc -g Ans4.c -Wall -o Ans4
	gdb Ans4
	
	to see registers put breakpoint
	eg. 
	b *0x00000000004005b8
	run
	info r
	
	this will show all the registers' values
	The screenshots "disasMain.png" and "reisters.png" show the outputs.
	Address binding happens at the load time.
	  




