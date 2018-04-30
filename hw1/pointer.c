/*
 * Type your name here:  Anthony Gasbarro
 *
 * Notice that function 'display_int' will dispslay an array of integers.
 * The function 'display_int_ptr' is another implementation of 'display_int'
 * but using only a pointer.  
 *
 * Now notice that function 'display_char' will display a string of
 * characters.  There is a function 'display_char_ptr' also displays
 * a string of characters.  Modify 'display_char_ptr' so it is
 * implemented using a pointer.
 */

#include <stdlib.h>
#include <stdio.h>



/* Function that displays the contents of an int array */
void display_int(int array[], int length) {
int i;

printf("Display integer array\n");
for (i=0; i<length; i++) {
   printf("%d\n", array[i]);
}
printf("\n");
}

/* Function that displays the contents of an int array using a pointer */
void display_int_ptr(int array[], int length) {
int *ptr;

printf("Display integer array using a pointer\n");
for (ptr = array; ptr < array+length; ptr++) {
   printf("%d\n", *ptr);
}
printf("\n");
}

/* Function that displays char string */
void display_char(char string[], int length) {
int i;

printf("Display string\n");
for (i=0; i<length; i++) {
   printf("%c", string[i]);
}
printf("\n");
}

/* Function that displays char string using a pointer */
void display_char_ptr(char string[], int length) {
char *ptr;


printf("Display string using a pointer\n");

for(ptr = string; ptr < string+length; ptr++){
	printf("%c", *ptr);
	}
}



/* Function that displays the contents of an int array using a pointer */

void main() {

int  array[10] = {12, 34, 56, 78, 90, 21, 43, 65, 87, 90};
char string[12] ="Hello World\n";

display_int(array, 10);
display_int_ptr(array, 10);
display_char(string, 12);
display_char_ptr(string, 12);

}
