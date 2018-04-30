/* Name:  Anthony Gasbarro
 *
 * This program will store words in a singly linked list.
 * It allows the user to append, delete, list, reverse, etc.
 *
 * The functions you have to change are "drop_node" and "reverse_list".
 * Note that "drop_node" is called by "delete2".
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Definitions

struct ListNode {
   char              word[100];
   struct ListNode * next;
   }; 

struct LinkedList {
   struct ListNode * head; // Head which points to first element in list
   };

// Function prototypes
char get_command();
void init_list(struct LinkedList *list);
void append_list(struct LinkedList *list);
void display_list(struct LinkedList *list);
void delete1(struct LinkedList *list);
void delete2(struct LinkedList *list);
void reverse_list(struct LinkedList *list);
void drop_node(struct ListNode * node);
void help();

void main()
{
char command;
struct LinkedList list;

init_list(&list);

do {
  command = get_command();
  switch(command) {
     case 'a': append_list(&list);
               break;
     case 'd': delete1(&list);
               break;
     case 'D': delete2(&list);
               break;
     case 'l': display_list(&list);
               break;
     case 'r': reverse_list(&list);
               break;
     case 'h': help();
               break;
     case 'e': printf("Exiting program\n");
     } 

  } while(command!='e');
}

// You must implement the following function that reverses the
// linked list.
//
void reverse_list(struct LinkedList *list)
{

// You can delete the following line
//printf("*** Warning *** Function reverse is not implemented\n");

	struct ListNode *prev = NULL;
	struct ListNode *curr = list->head;
	struct ListNode *next;
	
	while (curr != NULL)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;	
	}
	list->head = prev;
	
	
}


// You must implement the following function that will delete
// the node from the linked list.  The function is passed the reference
// 'node' to the node.  It's a little tricky since you don't have
// a reference to the previous node.  Your function must also free
// up the space of the deleted node.  This function is called by
// 'delete2'
//
void drop_node(struct ListNode *node)
{
// Delete the following line
//printf("Function drop_node doesn't work:  it didn't drop [%s] \n",node->word);

	struct ListNode *temp;
	
	temp = node->next;
	strcpy(node->word,node->next->word);
	node->next = temp->next;
	free(temp);
	

}

void delete2(struct LinkedList *list)
{

struct ListNode *current;
struct ListNode target;    // The word to delete

// Get the word to delete 
printf("Enter word to delete: ");
scanf("%s",target.word);

// Find the word in the linked list (if it's there).
current = list->head;
while (current != NULL) {
   if (strcmp(current->word,target.word)==0) break;
   current = current->next;
}

// Delete the node
if (current != NULL) drop_node(current);
else printf("[%s] is not in the list\n",target.word);
}


void delete1(struct LinkedList *list)
{
struct ListNode ** current_ref;
struct ListNode target;         // Stores the word to delete
struct ListNode * temp;

current_ref = &(list->head);    // current_ref points to "head" of list.

// Get the word to delete 
printf("Enter word to delete: ");
scanf("%s",target.word);
while(getchar() != '\n');   // Get rid of spurious characters entered

while (*current_ref != NULL) {
   if (strcmp((*current_ref)->word,target.word) == 0) break;
   current_ref = &((*current_ref)->next);
}

// The following deletes the node (if there one to delete)
if (*current_ref != NULL) {
   temp = *current_ref;
   *current_ref = (*current_ref)->next;
   free(temp);                            // Good housekeeping
}
else printf("[%s] is not in the list\n",target.word);
}

void init_list(struct LinkedList *list)
{
list->head = NULL;
}

void append_list(struct LinkedList *list)
{
int i;
int result;
struct ListNode * newentryptr;
struct ListNode ** lastptr;

newentryptr = (struct ListNode *) malloc(sizeof(struct ListNode));

if (newentryptr == NULL) {
   printf("Can't add to list, memory's full\n");
   return;
   }

// Initialize the new entry by getting a word  from the user
// and making the next pointer equal NULL

printf("Enter new word: ");
scanf("%s",newentryptr->word);
while(getchar() != '\n') {}   // Get rid of spurious characters entered
                              //  by the user
newentryptr->next = NULL; 

// Find the end of the linked list then append the new node.
lastptr = &(list->head); // Initializes lastptr to point to head
while (* lastptr != NULL) {  // Stop if you're at the end
   lastptr = &((*lastptr)->next); // lastptr is updated so it points to
                               // the next node's "next" member.
}  
// Note that the above can be written as a for-loop to make the code
// even more compact

// Now we add the new entry

* lastptr = newentryptr;

printf("Added '%s' to the list\n",newentryptr->word);
}

void display_list(struct LinkedList *list)
{
struct ListNode * node_ptr;

node_ptr = list->head;

if (node_ptr == NULL) {
   printf("List is empty\n");
   return;
   }

while (node_ptr != NULL) {
   printf("%s\n",node_ptr->word);
   node_ptr = node_ptr->next;
}

}

char get_command( )
{
char command;
int  valid;

do {
   printf("\nEnter command a(dd) d(elete) D(elete) l(ist) h(help) r(everse) or e(xit): ");
   command = getchar();
   while(getchar() != '\n') { } // Get rid of spurious characters
   switch(command){
      case 'a':
      case 'd':
      case 'D':
      case 'e':
      case 'h':
      case 'r':
      case 'l': valid = 1;
                break;
      default:  valid = 0;
                printf("Your entry '%c' is invalid!\n",command);
      }
   } while(valid == 0);

return(command);
}

void help()
{
printf("\nDescription of commands\n");
printf("   a:  Append a word to the list\n");
printf("   d:  Delete a word from the list\n");
printf("   D:  Delete a word from the list\n");
printf("   l:  List the list\n");
printf("   r:  Reverse the linked list\n");
printf("   e:  Exit the program\n");
printf("\n");
}

