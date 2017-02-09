In this all the files are in the pintos/src/tests/threads Folder.

FOR PART 1

1) Created a lab5.c and lab5.h file in the tests/threads directory and made functions test_hello to print "Hello World".
2) Added the line tests/threads_SRC += tests/threads/lab5.c in Make.tests to add this file to the list of files to be compiled by make command	
3) Added {"hello", test_hello}, in tests.c to call test_hello using pintos run hello.
4) Added extern test_func test_hello; to declare the function in the system.
5) In the directory src/threads I ran command make. 
6) To run the code run command pintos run hello.

FOR PART 2

1) In the file lab5 added a function test_sort to generate random numbers and sort them.
2) In the function hello thread_create("sortThread",PRI_DEFAULT,(thread_func *)test_sort,NULL); 
	This creates a thread by the name sortThread priority = PRI_DEFAULT which will run function test_sort with no arguments for test_sort.	 
3) Added {"hello", test_hello}, in tests.c so that it can also be run using pintos run sort.
4) Added extern test_func test_sort; to declare the function in the system.
5) In the directory src/threads I ran command make.
6) To run the code ran command pintos run hello.
7) This runs hello and then run test_sort in another thread.


How Threading system works in pintos

1) threads are created using thread_create().
2) context switching is done by function thread_switch().
3) pintos gives implements threads in first came first first serve basis (Priority is not implemented till now) as it uses lists_push_back in the function init_thread function that is used to initialise threads (in src/threads/thread.c)
4) This means that first the main thread will execute completely then the child thread (our created thread) will execute.
5) other functions like thread_yield ,thread_block ,thread_unblock etc. are also defined in thread.c which perform different tasks for threads like pausing the thread,blocking and unblocking threads respectively.

 


