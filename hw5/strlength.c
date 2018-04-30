/*
 Name: Anthony Gasbarro
 Due: Feb 15 2018
 */

/*
This program reads a string in and counts the longest continuous substring
of two different characters. It is still in O(n) due to the nature of the small
changes made. The initial for loop is left intact and small changes have been made to
the order in which checks and resets of counters are being tracked.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXLENGTH 100000

/*
 * Finds longest substring in 'str' with length 'length'
 *     The substring's starting index is 'first' and
 *     it's last index is 'last'.
 *     It returns the length of the substring.
 */


int strlength(char str[], int length, int *first, int *last);

void main(int argc, char *argv[])
{
if (argc != 2) {
	printf("Usage:  ./a.out  <data file>\n");
	return;
}

FILE *fp = fopen(argv[1], "r");
if (fp == NULL) {
	printf("Error in opening file: '%s'\n", argv[1]);
	return;
}
int length;
fscanf(fp, " %d ", &length);

if (length >= MAXLENGTH) {
	printf("Data is too large\n");
	return;
}

char *str = (char *)malloc(length*sizeof(char));
fgets(str, length+1, fp);

fclose(fp);
int first, last;
int n = strlength(str, length, &first, &last);

printf("String length = %d, first = %d, last = %d\n", n, first, last);

free(str);
}

int strlength(char str[], int length, int *first, int *last)
{
int best_first = 0;  /* Storage for the best string */
int best_last = 0;
int best_length = 1;

int curr_first = 0;  /* Keep track of the current string */
int symbol1 = str[0];
int symbol2 = str[0]; //added a variable to keep track of second symbol

//both symbol trackers are set to the same symbol until a new one is encountered

for (int i=0; i < length; i++) {

//if statement below was modified to check for if the current symbol matches
//neither of the two symbols being tracked. The condition below will reset
//both symbol trackers to the new symbol and reset the counting of new substring

	if ((str[i] != symbol1) && (str[i] != symbol2) || (i == length-1)) {
		if ((i - curr_first) > best_length) {
			best_first = curr_first;
			best_last = i;
			best_length = i - curr_first +1;

			//if neither of the symbols match or the end of the string has been reached
			//set both symbols being tracked to the new symbol.
			//make i the new current first and offset by 1 for index 0 being included

			symbol1= str[i]; symbol2 = str[i];
			curr_first = i+1;
		}
	}
	//If a second symbol is encountered the 2nd symbol tracker will be set
	//to the new symbol. The if statement above will account for if a third new
	//symbol is encountered.
	if (str[i] != symbol1 && str[i] != symbol2) { 
		symbol2 = str[i];

	}
}

*first = best_first;
*last = best_last;

return best_length;
}
