//FINAL EXAM EE 367

//Completed by: Anthony Gasbarro

/*
 * Function palinsub(char string[])
 * displays (on the console) the number of subsequences of a character
 * string that are palindromes.
 *
 * The program is run as follows:
 *
 * ./a.out <string file name>
 *
 * where <file> is the file name of a string of characters.
 * The program reads the character string in the file and stores
 * it in an array string[]. Assume the string has length at
 * most 1000.
 *
 * It then calls the function 'palinsub' which returns the
 * number of subsequences of the string that are palindromes.
 *
 * Currently, 'palinsub' doesn't work.  Write palinsub using
 * the bottom-up approach of dynamic programming.
 * You are allowed to add functions.
 *
 * Your palinsub algorithm should run as a polynomial function
 * of the length of string[].
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLENGTH 1000

/*
 * Open a file 'str_file'.  Then read it and put it in a
 * dynamically allocated buffer.  Return the pointer to the
 * buffer.
 */
char * file_str(char * str_file);

/*
 * Create and destroy an row x col int array
 *    Note that after: int ** a = create_array(row, col)
 *    then you can access the array using a[i][j]
 */
int ** create_array(int row, int col);
void destroy_array(int ** arr, int row);
int max(int x, int y);

/*
 * palinsub(string) which returns the number of substrings
 * of 'string' that are palindromes.
 */
int palinsub(char * string);

void main(int argc, char *argv[])
{
if (argc!=2) {
	printf("Usage:  ./a.out <string file name>\n");
	return;
}
char * string = file_str(argv[1]);
int string_size = strlen(string);
if (string_size > MAXLENGTH) {
	printf("File '%s' is too large (> %d bytes)\n", argv[1], string_size);
	return;
}

printf("The number of subsequences of '%s' that are palindromes: %d\n",
		string, palinsub(string));
}

//New palinsub function using O(n) space complexity

int palinsub(char * string)
{

int string_size = strlen(string);

//Initialize an array of size(string.length)
int memo[string_size];
//Outer for loop will start at end of string for comparison
	for(int i = string_size-1; i >= 0; i--){

		//backup variable is made to store unupdated values
		int b = 0;
		//inner for loop will choose the ending poiint of the string to compare
		for(int j = i; j < string_size; j++){

			//base case: if letter is compared to itself it is palindrome of length 1
			if(j == i){
				memo[j] = 1;
			}

			//if two variables being compared are equal
			//temp store the front variable and add the length of both char to the
			//memo'd total amount, b variable stores previous iteration of loop
			//before it was updated
			else if (string[i] == string[j]){
				int temp = memo[j];
				memo[j] = b+2;
				b = temp;
			}

			//store the current iteration of the 'j' memo value in a backup
			//variable and update the current max length
			else{
				b = memo[j];
				memo[j] = max(memo[j-1], memo[j]);
			}
		}
	}
//return the value found after all iterations
return memo[string_size -1];

}

int max(int x, int y){
	if(x > y){
		return x;
	}
	else{
		return y;
	}
}

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

char * file_str(char * str_file)
{
FILE * fp = fopen(str_file, "r");
if (fp == NULL) {
	printf("File '%s' didn't open\n", str_file);
	return 0;
}
fseek(fp, 0, SEEK_END);
long size = ftell(fp);
rewind(fp);
char *buf = (char *) malloc(sizeof(char)*(size+1));
if (buf==NULL) {
	printf("Couldn't allocate memory for file '%s'\n", str_file);
	return 0;
}
int result = fread(buf,1,size,fp);
if (result!=size) {
	printf("Didn't read the entire file '%s'\n", str_file);
	return 0;
}
size--;
buf[size] = '\0';
printf(">>>String in file '%s':\n",str_file);
printf("'%s'\n", buf);
printf("Length = %ld\n",size);
fclose(fp);
return buf;
}
