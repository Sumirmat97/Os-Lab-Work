This is the submission of lab 2 assignment

	to compile:
			1. $ gcc Ans1.c -Wall -o Ans1 
			2. $ ./Ans1

	to run without compiling:
			1. ./Ans1 

Note:
A space is required between each command and arguments of the command else it will not work.

What it does: 

1. It displays the current directory after which you can enter your command. If command is correct it executes otherwise displays "commmand not found". 

2. The commands that work are gedit, ls, mkdir, man, netstat, gcc, top, strace, exit, ctrl+D, clear, nano, pwd, cat, ps, clear, etc.
 
3. The processes can be run in both foreground and background. If a process is run in background using & the pid of the child is displayed on the shell. 

4 .It can also execute multiple commands in background	eg. ls & gedit file.txt &
	both these will run in the background just like the do in the shell provided by ubuntu.

5. It can also execute multiple commands using '&&'  eg. ls && cd .. && gedit file.txt 
	All of these commands will be executed one by one. 

6. It can also execute one pipeline operater in one statement 
	eg. 
	ls | more 
	cat Ans1.c | tail -n 10

7. There is no abrupt stop in the program
