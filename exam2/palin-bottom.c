//EE367 Midterm 2

//Completed By: Anthony Gasbarro
//Due April 6 2018

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

/*
 * palinsub(string) which returns the number of substrings
 * of 'string' that are palindromes.
 */
int palinsub(char * string);
int palrecurs(char * S, int ** a, int s, int e);

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

int palinsub(char * string)
{
int string_size = strlen(string);
int i = 0;
int j = string_size - 1;
int ** arr = create_array(string_size + 1, string_size + 1);

for (int row = 0; row < string_size; row++){
	for (int col = 0; col < string_size; col ++){
		arr[row][col] = 0;
	}
}

return palrecurs(string, arr, 0, string_size - 1);

}

int palrecurs(char * S, int ** a, int s, int e){
	if(s > e){
		return 0;
	}
	if(s == e){
		return 1;
	}
	if(a[s][e] > 0){
		return a[s][e];
	}

int ans = 0;

if(S[s] == S[e]){
	int l = s + 1;
	int r = e - 1;
	while (l <= r && S[l] != S[s]) ++l;
            while (l <= r && S[r] != S[s]) --r;
            if (l > r)
                ans = palrecurs(S, a, s + 1, e - 1) * 2 + 2;
            else if (l == r)
                ans = palrecurs(S, a, s + 1, e - 1) * 2 + 1;
            else
                ans = palrecurs(S, a, s + 1, e - 1) * 2
                    - palrecurs(S, a, l + 1, r - 1);
        } else {
            ans = palrecurs(S, a, s, e - 1)
                + palrecurs(S, a, s + 1, e)
                - palrecurs(S, a, s + 1, e - 1);
        }
					a[s][e] = ans;
				return a[s][e];
}

int ** create_array(int row, int col)
{
int ** arr = (int **) malloc(row*sizeof(int *));
for (int i=0; i < row; i++) {
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
