/*
 * Program for weave.c
 */

//Weave.c
//Completed by: Anthony Gasbarro

//This program performs a pairwise swap of the nodes in a linked list


#include <stdio.h>
#include <stdlib.h>

struct list_node {
	int key;
	struct list_node * next;
};

struct list_node * weave(struct list_node * head);
struct list_node * create_list(int n);
void destroy_list(struct list_node * head);
void display_list(struct list_node * head);



int main(int argc, char * argv[])
{

if (argc != 2) {
	printf("Usage: ./a.out <length of linked list.\n");
	return 0;
}

int n = atoi(argv[1]);
if (n < 2 || 2*(n/2) != n) {
	printf("Length = %d, but it's supposed to be a positive even integer\n", n);
	return 0;
}

struct list_node * head = create_list(n);
printf("Original linked list:\n");
display_list(head);

head = weave(head);
printf("Weaved linked list:\n");
display_list(head);

destroy_list(head);

return 1;
}


void display_list(struct list_node * head)
{
for (struct list_node * curr = head; curr!= NULL; curr=curr->next){
	printf("%d -> ", curr->key);
}
printf("/\n");
}

void destroy_list(struct list_node * head)
{
struct list_node * curr = head;
while (curr!=NULL) {
	struct list_node * temp = curr;
	curr = curr->next;
	free(temp);
}
}


struct list_node * create_list(int n)
{
struct list_node * new_node;
struct list_node * head;
struct list_node * last_node;

for (int i=0; i<n; i++) {
	new_node = (struct list_node *) malloc(sizeof(struct list_node));
        new_node->key = i;
	new_node->next = NULL;
	if (i==0) {
		head = new_node;
		last_node = new_node;
	}
	else {
		last_node->next = new_node;
		last_node = new_node;
	}
}
return head;
}


/*
 * The following function doesn't work; it doesn't weave.
 * Correct the function.
 */
struct list_node * weave(struct list_node * head)
{
	//if list is empty return list
	if(head == NULL){
		return head;
	}
//3 pointers are created to keep track of current, previous, and next nodes
	struct list_node *prev = head;
	struct list_node *curr = head->next;
	//swap head to #2 node
	head = curr;

	struct list_node *next = curr->next;
//loop will iterate through and rearrange pointers until NULL is found
//at which point the list is at the end and the function ends
	while(1){

		next = curr->next;
		curr->next = prev;

		if(next == NULL || next->next == NULL){
			prev->next = next;
			break;
		}

		prev->next = next->next;
		prev = next;
		curr = prev->next;
	}

	return head;
}
