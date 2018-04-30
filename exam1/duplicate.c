//Midterm 1 Duplicate.c

//Completed by: Anthony Gasbarro
//Due March 3, 2018
/*
 * Function duplicate( ) finds
 * duplicate a value in an array of integers of length n,
 * where the values range from 0 to n-2, i.e., n-1 distinct values.
 *
 * Note that since there are a smaller number of values than elements
 * in the array, there must be at least one duplicate.
 *
 * Assume there is only one duplicate number. Function duplicate() finds
 * of the duplicate values.  For example, if A[0] = A[7] = A[88] = 5
 * then 5 three times and duplicate() will
 * return 0, 7, or 88.
 */
#include <stdlib.h>
#include <stdio.h>

void permute(int num[], int length);
int random_num(int first, int last);
void display(int num[], int length);
int duplicate(int num[], int length);


int main(int argc, char * argv[]) {

if (argc!=2) {
	printf("Usage:  ./a.out <length of array>\n");
	return 0;
}
int length = atoi(argv[1]);  /* Length of array */
if (length < 2) {
	printf("Length = %d, but it must be larger than 1\n", length);
	return 0;
}

/*
 * Create an integer array 'num' with random integer values, so
 * that here is only one value that has a duplicate.  The value is
 * chosen at random.
 */
int * num = (int *) malloc(length*sizeof(int));
for (int i=0; i<length-1; i++) {
	num[i] = i;
}
srand48(1);
int temp = random_num(0,length-2);
temp = random_num(0,length-2);
printf("rand num = %d\n",temp);
num[length-1] = num[temp];
printf("Original values:\n");
display(num, length);

permute(num, length);
printf("Randomly permuted values:\n");
display(num, length);

/*
 *  Display the duplicate value and its location
 */
int k = duplicate(num, length);
printf("Duplicate value = %d\n",num[k]);
printf("Location of duplicate value = %d\n",k);


free(num);
return 1;
}

/*
 * Duplicate returns the location of a duplicate value
 * The array num[] has length 'length'
 * The values in the array are 0, 1, ..., length-2.
 * Currenly, this function doesn't work, so you must rewrite it
 * to make it work.
 */

 //duplicate is found using cycle detection method; O(n)
 
int duplicate(int num[], int length)
{
	if(length == 0)
	return -1;

	int slow = length-1;
	int fast = length-1;
	int finder = slow;

//first loop will be in order find the cycle of values
	while(1){
		//since the range is bounded by length-2
		//all values are also addresses within the array
		//'slow' increments using integers as array addresses
		//'fast' increments the same way at double speed
		slow = num[slow];
		fast = num[num[fast]];

		//loop is broken once duplicate is found
			if (slow == fast)
					break;
					}
		//second loop is to iterate through and find the location of the duplicate
		while(1){

			if (num[slow] == num[finder])
			return slow;

			slow = num[slow];
			finder = num[finder];
		}
}



void display(int num[], int length)
{
for (int i=0; i<length; i++) {
	printf("%d  ", num[i]);
}
printf("\n");
}


int random_num(int first, int last)
{
double random_value = drand48()* ((double) (last - first + 1));
int random_int = random_value;
return first + random_int;
}


void permute(int num[], int length)
{
for (int i=0; i<length; i++) {
	int k = random_num(i,length-1);
	int temp = num[i];
	num[i] = num[k];
	num[k] = temp;
}
}
