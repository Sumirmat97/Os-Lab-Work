#include<stdio.h>
#include"myFile.h"

int main() {
   double num;
   printf("Enter a number: ");
   scanf("%lf",&num);
   num = getRoot(num);
   printf("Square root of number : %.2lf\n", num);
   return 0;
}


