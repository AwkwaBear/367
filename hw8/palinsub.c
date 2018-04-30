//Longest common Subsequence EE367 HW#8
//Completed by: Anthony Gasbarro
/*

 * Function palinsub(char string[])
 * displays (on the console) the longest palindrome substring
 * of string[].
 * (string1[] is terminated by the null char '\0'.)
 *
 * The current function lcs doesn't work -- it's incomplete.
 * Make it work, by applying either top-down (with memoization) or
 * bottom-up dynamic programming.
 *
 * Your algorithm should run in a reasonable amount of time,
 * even if the strings have length of 1000.
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

void lcs(char * string1, char * string2);
int max(int x, int y);

int max(int x, int y){
  if (x>y){return x;}
  else{return y;}
}

/*
 * Create and destroy an row x ccl int array
 *    Note that after: int ** a = create_array(r, c)
 *    then you can access the array using a[i][j]
 */
int ** create_array(int row, int col);
void destroy_array(int ** arr, int row);

/*
 * palinsub(string)
 * displays the longest palindrome subsequence.
 */

 void lcs(char * string1, char * string2)
 {
 	int m = strlen(string1);
 	int n = strlen(string2);
 	int ** a = create_array(m+1, n+1);

 	for (int i = 0; i <= m; i++){
 			for (int j = 0; j <= n; j++){
 					if(i == 0 || j == 0){
 						a[i][j] = 0;
 					}
 					else if(string1[i-1] == string2[j-1]){
 						a[i][j] = a[i-1][j-1] + 1;
 					}
 					else{
 						a[i][j] = max(a[i-1][j], a[i][j-1]);
 					}

 				}
 			}

    int index = a[m][n];



int i = m;
int j = n;

 while(i>0 && j> 0){
   if (string1[i-1] == string2[j-1]){
     printf("%c", string1[i-1]);
     i--;
     j--;
   }
   else if(a[i-1][j] > a[i][j-1]){
     i--;
   }
   else{
     j--;
   }

 }

printf("\n");

}

void palinsub(char * string);

void palinsub(char * string){
int string_size = strlen(string);

char rev[string_size];
 int end = string_size-1;

for(int i = 0; i < string_size-1; i++){
	rev[i] = string[end];
	end--;
 }
 lcs(string, rev);
}
void main(int argc, char *argv[])
{
if (argc!=2) {
	printf("Usage:  ./a.out <string>\n");
	return;
}
char * string = file_str(argv[1]);
int string_size = strlen(string);
if (string_size > MAXLENGTH) {
	printf("File '%s' is too large (> %d bytes)\n", argv[1], string_size);
	return;
}

printf("Longest palindrome subsequence of '%s'':\n", string);
palinsub(string);
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
