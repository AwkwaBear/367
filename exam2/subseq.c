//EE367 Midterm 2

//Completed By: Anthony Gasbarro
//Due April 6 2018

/*
 * This program will generate an array val[] of integers 0, 1, ..., n-1,
 * where n is the length of the array.  Then it will randomly permute
 * the array, each permutation being equally likely.
 *
 * Then it will call a function 'subseq' that finds the
 * length of the longest increasing subsequence of the array.
 * It will display the length of the longest subsequence,
 * and the subsequence itself..
 *
 * Function 'subseq' currently does not work.
 * Implement the function using the top-down approach with memoization.
 * You may add functions.
 * Function 'subseq' and your functions
 * should have an overall time complexity of O(n^2).
 */
#include <stdlib.h>
#include <stdio.h>

void permute(int val[], int length);
int random_num(int first, int last);
void display(int val[], int length);
void subseq(int val[], int length);

int ** create_array(int row, int col);
void destroy_array(int ** arr, int row);

int main(int argc, char * argv[]) {

if (argc!=2) {
	printf("Usage:  ./a.out <length of array>\n");
	return 0;
}
int length = atoi(argv[1]);  /* Length of array val[] */
if (length < 2) {
	printf("Length = %d, but it must be larger than 1\n", length);
	return 0;
}

/*
 * Create an integer array 'val' with random integer values, so
 * that here is only one value that has a duplicate.  The value is
 * chosen at random.
 */
int * val = (int *) malloc(length*sizeof(int));
for (int i=0; i<length; i++) {
	val[i] = i;
}
printf("Original values:\n");
display(val, length);

srand48(1);
permute(val, length);
printf("Randomly permuted values:\n");
display(val, length);

subseq(val, length);

free(val);
return 1;
}

/*
 * Function 'subseq' will display the length of the longest
 * increasing subsequence of array val[], which has length 'length'.
 * It will also display the subsequence itself.
 */
void subseq(int val[], int length)
{
int * lisarr;
int * print;
int i = 0;
int j = 0;
int max = 0;
int temp = 0;
int index = 0;

print = (int *) malloc(length*sizeof(int));
int p = 0;

//Create dynamic array for storing answers to subproblems and initialize value to 1
lisarr = (int *) malloc(sizeof(int) * length);

for (i = 0; i < length; i++){
	lisarr[i] = 1;
}

print[p] = val[0]; p++;
//compute subproblem solutions
for(i = 1; i < length; i++){
	for (j = 0; j < i; j++){
		if(val[i] > val[j] && lisarr[i] < lisarr[j] + 1){
			lisarr[i] = lisarr[j] + 1;
			if(val[i] > print[p]){
				print[p] = val[i];
				p++;
			}
		}
	}
}

for(i = 0; i < length; i++){
	if (max < lisarr[i]){
		max = lisarr[i];

	}
}

printf("Length of the longest increasing subsequence:\n");
printf("%d \n", max);


printf("Longest increasing subsequence:\n");
for(p=0; p < max; p++){
	printf("%d ", print[p]);
}
printf("\n");

return;
}


void display(int val[], int length)
{
for (int i=0; i<length; i++) {
	printf("%d  ", val[i]);
}
printf("\n");
}

int random_num(int first, int last)
{
double random_value = drand48()* ((double) (last - first + 1));
int random_int = random_value;
return first + random_int;
}

void permute(int val[], int length)
{
for (int i=0; i<length; i++) {
	int k = random_num(i,length-1);
	int temp = val[i];
	val[i] = val[k];
	val[k] = temp;
}
}

/*
 * Create and destroy an row x col int array
 *    Note that after: int ** a = create_array(row, col)
 *    then you can access the array using a[i][j]
 *    You can use this to create a memo array.
 *    On the other hand, you may not need it if your
 *    memo array is a 1-dimensional.
 */
int ** create_array(int row, int col);
void destroy_array(int ** arr, int row);


int ** create_array(int row, int col)
{
int ** arr = (int **) malloc(row*sizeof(int *));
for (int i=0; i<row; i++) {
	arr[i] = (int *) malloc(col*sizeof(int));
}
return arr;
}

void destroy_array(int ** arr, int row)
{
for (int i=0; i<row; i++) {
	free(arr[i]);
}
free(arr);
}
