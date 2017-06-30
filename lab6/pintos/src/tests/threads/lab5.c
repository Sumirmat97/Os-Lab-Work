#include <stdio.h>
#include <stdlib.h>
#include <list.h>
#include <threads/malloc.h>
#include "lab5.h"
#include <kernel/console.h>
#include <random.h>
#include <devices/timer.h>
#include "threads/thread.h"

struct number{
	struct list_elem elem;
	int data;
}*num;

struct list number_list;

// function to be used by sort in checking the elements
static bool smaller(const struct list_elem *one, const struct list_elem *two,void *aux UNUSED) 
{
  const struct number *a = list_entry (one, struct number, elem);
  const struct number *b = list_entry (two, struct number, elem);
 
  return a->data < b->data;
}
			
void test_display(void *aux UNUSED)
{
	
	int i,j;
	struct thread *currentThread = thread_current();
	struct list_elem *e=NULL;
	struct number *f=NULL; 
			
	printf("Priority of the third thread: %d\n",currentThread->priority);
	//displaying the sorted list
	printf("The numbers after sorting are: \n");
	for (e = list_begin (&number_list); e != list_end (&number_list); e = list_next (e))
	{
		f = list_entry (e, struct number, elem);
		printf("%d\n",f->data);		
	}		

}

void test_sort(void *aux UNUSED)
{

	int i,j;
	struct thread *currentThread = thread_current();
	printf("Id of the second thread: %d\n",currentThread->tid);
	
	list_sort(&number_list,smaller,NULL);

		
}

void test_generate(void *aux UNUSED)
{
	int i,j;
	struct thread *currentThread = thread_current();

	printf("Name of the first thread: %s\n",currentThread->name);

	list_init(&number_list);
	
	num = (struct number*)malloc(sizeof(struct number));
	
	//initialise the list using random numbers
	for(i=0;i<10;i++)
	{
		random_bytes(&num[i].data,sizeof(int));	//generate random values
		num[i].data /= 10000029;		//reducing the value of data in num 
		list_push_back(&number_list,&num[i].elem);//push back the element in the list
	}

		
}

void test_hello(void)
{
	int i,j;
	
	printf("\nHello World.\n");
	contextSwitchesCounter=0;
	//creates thread to genrate random numbers and sort them in list
	thread_create("generateNo",PRI_DEFAULT,test_generate,NULL);
	//creates second thread that sorts the list
	thread_create("sortThread",PRI_DEFAULT,test_sort,&number_list);
	//create third thread that displays the sorted list
	thread_create("displayList",PRI_DEFAULT,test_display,&number_list);
		
	thread_yield();
	
		
	for(i=0;i<100000;i++)
		for(j=0;j<5000;j++)
			{};


	thread_print_stats();
	
	
}

