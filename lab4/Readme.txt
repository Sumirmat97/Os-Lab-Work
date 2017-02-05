This assignment required to create a system call that printed "Hello world" in kernell log file.

The folder hello contains the C code and the makefile to facilitate compilation of this C file along with kernel.

Changes were also made in syscall.h to add the declaration of the new system call and in syscall_64.tbl to tell the system where is the code of the system call "mySysCall" .

The kernel was then compiled and installed.

The file mySysCallRun calls the system call "mySysCall" and prints the returned value.

We can check that "Hello world" was written on th log file by using command dmesg.
    
