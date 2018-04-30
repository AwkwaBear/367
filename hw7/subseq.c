
//EE367 Subseq.c

//Anthony Gasbarro
//Due March 9, 2018


/*
 * Function subseq(char target[], char key[]) returns
 * the number of occurrences that the string 'key' is a
 * substring of 'target'.
 * (Note that both strings are terminated by the null char '\0'.)
 * Note that substrings are distinct if they have distinct locations.
 *
 * As an example, suppose target = 'rabbbit' and key = 'rabbit'.
 * Then subseq will return 3.
 *
 * The current function subseq doesn't work -- it's incomplete.
 * Make it work.  This may require adding new functions.
 * Use the top-down approach where you implement a recursive
 * algorithm with memoization.  Your algorithm should run in
 * a reasonable amount of time, even if the strings have
 * length of 1000.
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

int max(int a, int b);
/*
 * Create and destroy an row x ccl int array
 *    Note that after: int ** a = create_array(r, c)
 *    then you can access the array using a[i][j]
 */
int ** create_array(int row, int col);
void destroy_array(int ** arr, int row);

/*
 * subseq(target, key) returns the number of times string 'key' is
 * a substring of string 'target'.  The substring does not have to
 * be contiguous.  Also substrings at different locations are considered
 * distinct.
 */
int subseq(char * target, char * key);

void main(int argc, char *argv[])
{
if (argc!=3) {
	printf("Usage:  ./a.out <target string> <key string>\n");
	return;
}
char * target = file_str(argv[1]);
int target_size = strlen(target);
if (target_size > MAXLENGTH) {
	printf("File '%s' is too large (> %d bytes)\n", argv[1], target_size);
	return;
}
char * key = file_str(argv[2]);
int key_size = strlen(key);
if (key_size > MAXLENGTH) {
	printf("File '%s' is too large (> %d bytes)\n", argv[2], key_size);
	return;
}

printf("Number of occurences of '%s' in '%s': %d\n",key, target,
		subseq(target,key));

}

int subseq(char * target, char * key)
{
int t_size = strlen(target);
int k_size = strlen(key);
//printf("Doh!\n");  /* Delete this line */

int ** a = create_array(t_size+1, k_size+1);
//Initialize array
for (int i = 0; i <= t_size; i++){
		for (int j = 0; j <= k_size; j++){
				a[i][j] = 0;
	}
}
//Calculate dynamic array values
for (int i = 1; i <= t_size; i++) {
		for (int j = 1; j <= k_size; j++) {

			if (target[j - 1] == key[i - 1])
					a[i][j] = 1 + a[i - 1][j - 1];
			else
					a[i][j] = a[i][j - 1];

	}
}

//scroll through array rows and determine the largest substring
int ans = 0;
for (int i = 1; i <= t_size; i++){
		ans = max(ans, a[i][k_size]);
}
//return the value to the original function
return ans;
}

int max(int a, int b){
	if (a > b){
		return a;
	}
	else {
		return b;
	}
}

/* Hint:  return subseq_rec(target, t_size, key, k_size);
 * So you need to create another function.
 * You also need to include memoization
 */


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
