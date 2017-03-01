/*To implement safety algorithm */

#include <stdio.h>
#include <stdlib.h>

int main()
{
	
	int numRes,numPro;
	printf("Enter the number of process: ");
	scanf("%d",&numPro);
	printf("\nEnter the number of type of resources: ");
	scanf("%d",&numRes);
	
	int i,j;
	int *seq = (int *)malloc(sizeof(int)*numPro);
	int *MaxRes = (int *)malloc(sizeof(int)*numRes);
	int *sum = (int *)malloc(sizeof(int)*numRes);
	
	int Allocated[10][6];
	int Max[10][6];
	int need[10][6];
	int Available[6];
	
	printf("\n\nEnter the max number of instances per resource available: \n");
	for(i=0;i<numRes;i++)
	{
		printf("Enter the max number of instances available for resouce %d: ",i+1);
		scanf("%d",&MaxRes[i]);
	}
	
		
	printf("\n\nEnter the Max. need of resources by processes: \n");
	for(i=0;i<numPro;i++)
	{
		printf("Enter the Max. need of process %d\n",i+1);
		for(j=0;j<numRes;j++)
		{	
			printf("Enter the max need instances of resource %d: ",j+1);
			scanf(" %d",&Max[i][j]);
		}
	}
	
	printf("\n\nEnter the current allocation of processes: \n");
	for(i=0;i<numPro;i++)
	{
		printf("Enter the current allocation of process %d\n",i+1);
		for(j=0;j<numRes;j++)
		{	
			printf("Enter the current allocation of resource %d: ",j+1);
			scanf(" %d",&Allocated[i][j]);
		}
	}
	
	
	for(i=0;i<numPro;i++)
	{
		for(j=0;j<numRes;j++)
		{
			need[i][j] = Max[i][j] - Allocated[i][j];
			if(need[i][j] < 0)
			{
				printf("The allocated resource for %d is more than the max resource defined\n",i);
				exit(1);
			}
		}
	}
	
	
	for(i=0;i<numRes;i++)
	{
		for(j=0;j<numPro;j++)
		{	
			sum[i] = sum[i] + Allocated[j][i];  
		}
		Available[i] = MaxRes[i] - sum[i];  
		if(Available[i] < 0)
		{
			printf("The number of max instance is less than used resources\n");
			exit(1);
		}
		
	}
	
	printf("\n\nEnter the sequence you want to test(indexing begins from 1): ");
	for(i=0;i<5;i++)
	{
		printf("\nEnter the %dth process: ",i+1);
		scanf(" %d",&seq[i]);
		seq[i]--;
	}	
	for(i=0;i<5;i++)
	{
		if((need[seq[i]][0] <= Available[0]) && (need[seq[i]][1] <= Available[1]) && (need[seq[i]][2] <= Available[2]))  
		{
			Available[0] +=  Allocated[i][0];
			Available[1] +=  Allocated[i][1];
			Available[2] +=  Allocated[i][2];
		}
		else
		{
			printf("\nThe sequence is not safe\n");
			exit(0);
		}
		
	}
			printf("\nThe sequence is safe\n");
	
	return 0;
}
