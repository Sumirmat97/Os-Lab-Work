This assignment required to create a system call that printed "Hello world" in kernel log file.

How was this done:
1. downloaded the latest kernel from kernel.org (4.9.8)
2. made a folder inside the extracted folder by the name of hello.
3. inside the hello folder made a hello.c and made the system call function by the name mySysCall(void) (present in the folder uploded by the name lab4).
4. also made the Makefile to compile hello.c (present in the folder uploded by the name lab4).
5. changed the file Makefile present in linux-4.9.8/ replaced the line core-y += kernel/ mm/ fs/ ipc/ security/ crypto/ block/ to core-y += kernel/ mm/ fs/ ipc/ security/ crypto/ block/ hello
6. in file syscalls.h (present in linux-4.9.8/include/linux/) added the declaration of the newly created system call (asmlinkage long mySysCall(void);).
7. in the file linux-4.9.8/arch/x86/entry/syscalls/syscall_64.tbl added 548    common    hello    mySysCall
8. commands run to compile and install:
	sudo make menuconfig
	make -j 4
	sudo make modules_install install (after successful compilation).
9. to see the changes made after installation restarted the system using reboot command.
10.Created a userspace program by the name of mySysCallRun.c (present in the folder uploded by the name lab4).
11.Compiled the code using gcc and ran it using ./a.out
12.to see the message in the log file command used was dmesg.

