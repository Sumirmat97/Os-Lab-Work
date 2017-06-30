#include<stdio.h>
#include<stdlib.h>
#include<list.h>
#include "lab5.h"
#include<kernel/console.h>
#include<random.h>
#include "threads/thread.h"

void test_sort()
{
	int arr[10],i,j,smallPos,temp;

	random_bytes(arr,10*sizeof(int));	//generate random values
	
	for(i=0;i<10;i++)			//make the numbers small in value
		arr[i] /= 10000029;

	//selection sort 
	for(i=0;i<10;i++)
	{
		smallPos = i;
		for(j=i+1;j<10;j++)
		{
			if(arr[j] < arr[smallPos])
				smallPos = j;
		}
		if(smallPos != i)
		{
			temp = arr[smallPos];
			arr[smallPos] = arr[i];
			arr[i] = temp;
		}
	}

	//displaying the sorted array
	printf("The numbers after sorting are: ");
	for(i=0;i<10;i++)
		printf("\n%d",arr[i]);
	printf("\n");
}

void test_hello(void)
{
	printf("\nHello World.\n");
	thread_create("sortThread",PRI_DEFAULT,(thread_func *)test_sort,NULL);
}

