Team members: Nilesh Agarwal 2015KUCP1004
			  Sumir Mathur 2015KUCP1017

What was done to configure the system for implementing syscalls:

	1. In pintos and pintos.pm files changed the path of loader.bin and kernel.bin 
	2. make in src/examples
	3. In process.c in function process_wait add "while(1);" before return statement
	4. In setup_stack do change "*esp = PHYS_BASE;" to "*esp = PHYS_BASE - 12;"
	5. make in src/userprog
	6. After this we get a build folder in the userprog directory.
	7. in syscall.c we have to implement the functionality of kernel space programs that will do some specific work. These are the system calls.
	
How were the system calls implemented:
	1. Initialised an integer pointer with the value of stack pointer (int *p = f->esp;)
	2. Now we have to check which system call was called. 
	3. This was done by puting the value of pinter p in switch case and checking it against the values of given in syscall-nr.h
	4. if the value is SYS_HALT that means halt system call was asked for.
	5. A function by the name of halt is called which is defined in the same file i.e. syscall.c 
	6. This function then calls shutdown_power_off function defined in src/devices folder which shuts down the system and before that prints a statement which says
		"System is shutting down due to halt system call!!".
	7. The halt function takes no arguments.
	
	8.if the value is SYS_EXIT 

do those first two steps to create filesystem and format it.

then do 
pintos -p ../../examples/halt -a halt -- -q
pintos -q run 'halt' 

Made changes in thread.c and thread.h added functions their declarations and and added members in struct thread 
Also in syscall.h declartions were added and functions were made in  syscall.c

added bool thread_alive() in thread.c and its declaration in thread.h
 
