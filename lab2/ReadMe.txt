This is the submission of lab 2 assignment

It displays the current directory after which you can enter your command.

The commands that work are gedit ls mkdir man netstat gcc top strace exit ctrl+D clear nano pwd cat ps clear
 
The processes can be run in both foreground and background. If a process is run in background using & the pid of the child is displayed on the shell. 

It can also execute multiple commands in background	eg. ls & gedit file.txt &
both these will run in the background just like the do in the shell provided by ubuntu.

It can also execute multiple commands using '&&'  eg. ls && cd .. && gedit file.txt
All of these commands will be executed one by one. 
