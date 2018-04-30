/*
 *  Type your name here:  Name:  Anthony Gasbarro
 *
 *  This short program applies function pointers.
 *  The program will first fill an array with
 *  pseudo random numbers.  Then it will display
 *
 *     > the sum of the array
 *     > the minimum value of the array
 *     > the maximum value of th array
 *
 *  There is a missing typedef for a function pointer
 *  data type.  
 *
 *  Make the change where the comment starts with "INSERT HERE"
 *
 *  When it's correct, you can compile by gcc hw1.c 
 */

#include <stdlib.h>
#include <stdio.h>
#define MAXLENGTH 20

int sum_oper(int a, int b);
int max_oper(int a, int b);
int min_oper(int a, int b);

/* INSERT HERE: Missing typedef for "process_oper".  It's a function pointer */

typedef int (*process_oper)(int, int);

process_oper arrayFp[3] = {sum_oper, max_oper, min_oper};
/*  
 *  Operations applied to the array
 *
 *     o  sum_oper is used to sum the array
 *     o  max_oper is used to find the maximum of the array
 *     o  min_oper is used to find the minimum of the array 
 */
int sum_oper(int a, int b)
{
return a+b;
}

int max_oper(int a, int b)
{
if (a > b) return a;
else return b;
}

int min_oper(int a, int b)
{
if(a < b) return a;
else return b;
}

/*
 *  process_array will process an integer array.  A function
 *  pointer "oper" is passed to it.  It is assumed that
 *  "length" is greater than 1.
 */

int process_array(int a[], int length, process_oper oper)
{
int i;
int result=a[0];

for (i=1; i<length; i++) {
   result = oper(a[i],result);
} 

return result;
}

/*
 *  init_array will initialize an array with pseudo random values.
 */
void init_array(int a[], int length)
{
int i;
int pseudorand = 31; /* Some initial seed value */

for (i=0; i<length; i++) {
   pseudorand = (31*pseudorand + 17)%length;
   a[i] = pseudorand;
}

printf("Values of array\n");
for (i=0; i<length; i++) {
   printf("a[%d] = %d\n",i,a[i]);
}
}


void main()
{
int data[MAXLENGTH];
int i;

init_array(data, MAXLENGTH);

printf("Sum result = %d\n", process_array(data, MAXLENGTH, sum_oper));
printf("Max result = %d\n", process_array(data, MAXLENGTH, max_oper));
printf("Min result = %d\n", process_array(data, MAXLENGTH, min_oper));

}

