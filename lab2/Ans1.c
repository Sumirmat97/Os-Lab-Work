#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
  char input[100];
  do
  {
    printf("Name/computer$ ");
    fgets(input,100, stdin);
    if(strcmp(input,"\n")) //print the input only if not \n
      printf("%s\n",input);
  }while(strcmp(input,"exit"));

  return 0;  
}
