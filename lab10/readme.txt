Team members: Nilesh Agarwal (2015KUCP1004)
              Sumir Mathur (2015KUCP1017)

What was done to configure the system for implementing syscalls:
    1. In pintos and pintos.pm files we changed the path of loader.bin and kernel.bin
    2. make in src/examples
    3. In process.c in function process_wait add "while(1);" before return statement
    4. In setup_stack do change "*esp = PHYS_BASE;" to "*esp = PHYS_BASE - 12;" as we are not implementing argument passing from command-line.
    5. make in src/userprog
    6. After this we get a build folder in the userprog directory.
    7. In syscall.c we have to implement the functionality of kernel space programs that will do    some specific work. These are the system calls.
    
How were the system calls implemented:
    1. In syscall.c we need to implement a function named - ‘syscall_handler’ to handle all the
system calls in the kernel space. 
    2. When a user program need to execute a system call then it registers an interrupt and that interrupt is handled by calling this syscall_handler function. 
	3.This function takes an argument ‘struct intr_frame * f’ which has a integer pointer ‘esp’ that indicates the top of stack which we use to identify system call called in the user space as for each system call the top of the stack is always the system call number and now we can execute the corresponding system call in the kernel space.
    4. Now we have to check which system call was called.
    5. This was done by putting the value of pointer p(which holds the value to the top of the stack i.e the system call number) in switch case and checking it against the enums given in syscall-nr.h
    6. For example if the value is SYS_HALT, it  means that halt system call is called.
    7. A function named halt is called which is defined in the same file i.e. syscall.c
    8. This function then calls shutdown_power_off function defined in src/devices folder which
      shuts down the system and before that prints a statement which says
     “System is shutting down due to halt system call!!”.
    9. The halt system call takes no arguments.
    10. There are other system calls which take arguments. These arguments are stored in the stack and hence can be extracted by decrementing the esp pointer and storing the value.
These all system calls can be implemented by using the various functions defined in the kernel space with some checking.

Steps for running the system call : 
	1.Go to ‘src/examples’ folder, make a ‘filename.c’ file and write a program in that file to call a system call.
	2.Add this file to the Makefile of the directory and do ‘make’
	3.Then go to ‘src/userprog/build’ and write the following on terminal-

		A. pintos-mkdisk filesys.dsk --filesys-size=2
		B. pintos -f -q
		C. pintos -p ../../examples/filename -a filename-- -q
		D. pintos -q run ‘filename’

First command makes a file system for the pintOS to load and run the programs.
Second command formats the file system.
Third command loads a program binary into the file system from the ‘src/examples’ directory.
Fourth command runs the loaded program onto pintOS.

Following changes are made  in thread.c and thread.h: 
Some extra fields were added  in  the structure “struct thread” in thread.h file. These fields are being used by the system calls.
