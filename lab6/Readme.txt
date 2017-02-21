In this all the files are in the pintos/src/tests/threads Folder.

files changed lab5.c and lab5.h 

FOR PART 1

1) Removed the timer_sleep() function.
2) Added thread_yield() function at the same place.

This function pushes the current running thread back in the ready list hence switches context and starts the executing the sortThread which sorts the elements in the list.
Have used list API. 
After the execution of sortThread hello is executed and the process ends.  
  
FOR PART 2

1)Made two more functions test_generate and test_display
2)test_generate uses random_bytes and a list is initialised to some random values.
3)This list is passed to test_sort where list_sort is used to sort the list (defined in list.c)
4)This is then sent to test_display where it is displayed
5)Also the first thread displays its name, second thread displays its Id, third thread displays its Priority.
6)The thread which runs the test_hello function is pushed back in ready list so that it is rescheduled and the three functions execute before the test_hello finishes.
7)To make the FCFS value of macro TIME_SLICE was made 50 ticks. This is defined in thread.c in src/threads.

FOR PART 2.1
1)Added an extern variable in thread.h by the name of contextSwitchCounter;
2)Made the counter increment the value in each context swtich by adding the contextSwitchCounter++ in schedule function in thread.h
3)In thread_print_stats displayed this value of contextSwitches.
4)By this we can calculate the number of iterations of a thread (total context switches by total number of threads).
5)The value of TIME_SLICE was changed to get different values for no. of iterations.
5)Graph was plotted as follows.

FOR PART 2.2


How to run:
1) On terminal write: pintos run hello
