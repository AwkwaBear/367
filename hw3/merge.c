
// Name: Anthony Gasbarro

/* 
 * Mergesort is implemented in function 'mergesort', which is
 * implemented using recursion. 
 * Change mergesort so that it is implemented iteratively and
 * still has O(n log n) time complexity.
 */

#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>

#define MAXLENGTH 1000 

//Define function to return min of two integers

int min(int x, int y){return(x < y)? x :y;}


/* Initializes array a[] wih random values */
void init(int a[], int length); 

/* Displays array a[] */
void display(int a[], int length); 

/* 
 * Merges sorted subarrays 
 *    (a[last], a[last+1],..., a[midpt-1))
 *    (a[midpt], a[midpt+1], ..., a[last-1])
 * into a sorted array.
 */
void merge(int a[], int first, int midpt, int last);

/*
 * Change the following recursive implementation of mergesort 
 * into an iterative implementation.
 */
void mergesort(int a[], int first, int last);        /* Merge sort */

void main(int argc, char* argv[]) 
{
if (argc != 2){
	printf("Usage:  ./a.out <length of array>\n");
	return;
}
int length = atoi(argv[1]);
if (length >= MAXLENGTH) {
	printf("Length %d must be less than %d\n",length,MAXLENGTH);
	return;
}

/* Initialize and display the array */
int a[MAXLENGTH];       /* Array of data */
init(a, length);    
printf("\nInitial array:\n");
display(a, length);    

/* Sort and display the array */
mergesort(a, 0, length);
printf("\nSorted array:\n");
display(a, length);    
}

/* 
 * Mergesort:  Sorts the values in a[first], a[first+1],..., a[last-1] 
 * This is a recursive implementation.
 *
 * Change this into an iterative implementation  
 * that has O(n log n) time complexity.
 */

void mergesort(int a[], int first, int last)
{


int midpt;
//Determine Midpoint	
midpt = (first+last)/2;

	int curr_size; // variable to store current size
	
	//separate each variable into a complete sorted array by first separating into arrays of size 1
	//then merge doubling array size each time
	for (curr_size = 1; curr_size <= last-1; curr_size = 2*curr_size)
	{
		for(first = 0; first < last-1; first += 2*curr_size)
		{
			int mid = first + curr_size - 1;
			
			int right_end = min(first + 2*curr_size -1, last - 1);
			
			//Call the rewritten merge fuction
			merge(a, first, mid, right_end);
			
		}
	}
	
	
/* This is the REMOVED recursive approach

if (first < midpt-1) mergesort(a, first, midpt);
if (midpt < last-1) mergesort(a, midpt, last);
merge(a, first, midpt, last);
*/


}


/*
 * Merges two sorted subarrays (sorted in increasing order)  
 *    (a[first], ..., a[midpt-1]) and
 *    (a[midpt],..., a[last-1]) 
 *    into
 *    subarray temp[first],..., temp[last-1] in increasing order.
 *    
 *    Then it copies temp[first],..., temp[last-1] back into
 *    a[first],..., a[last-1].
 */
void merge(int a[], int first, int midpt, int last)
{

	int i, j, k; //counter variables for each array
	int n1 = midpt - first + 1; 
	int n2 = last - midpt;
	

	int A[n1], B[n2];
	
	//copy the data into each separate array
	for(i=0; i < n1; i++)
		{
			A[i] = a[first+i];
		}
	for(j=0; j < n2; j++)
		{
			B[j] = a[midpt + 1 +j];
		}

	//merge arrays one slot at a time comparing to determine ascending order
	i=0;
	j=0;
	k = first;	

	while(i < n1 && j < n2)
	{
		if(A[i] <= B[j])
			{
				a[k] = A[i];
				i++;
			}
		else
			{
				a[k] = B[j];
				j++;
				
			}
		k++;
	}
	
	//copy remaining elements of each separate array to final array
	while( i < n1)
	{
		a[k] = A[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		a[k] = B[j];
		j++;
		k++;
	}
}
/* This is the REMOVED recursive approach	
	static int temp[MAXLENGTH];

int leftptr;   
int rightptr;
int k;         
int delay;

leftptr = first;
rightptr = midpt; 


for(k=first; k<last; k++) {
   if (leftptr >= midpt) temp[k] = a[rightptr++];
   else if (rightptr >= last) temp[k] = a[leftptr++];
   else if (a[leftptr] < a[rightptr]) temp[k] = a[leftptr++];
   else if (a[leftptr] >= a[rightptr]) temp[k] = a[rightptr++];
   else printf("There's a bug \n"); 
	
	
*/
	

	



/* Initializes array a[] with random values. */
void init(int a[], int length)
{
int temp; 
int k;

for (int i=0; i<length; i++) a[i] = i; /* Initialize with distinct values */

/* Randomly shuffle the values */
srand48(1);     /*  Seed the pseudorandom number generator */
for (int i=0; i<length; i++) {
   k = lrand48()%(length-i);
   temp = a[k];
   a[k] = a[length-i-1];
   a[length-i-1] = temp; 
}
}

/* Displays the values in the array a[] */
void display(int a[], int length)
{
for (int i=0; i<length; i++) {
   printf(" %d ", a[i]);
   if ((i+1)%10 == 0) printf("\n");
}
printf("\n");
}


