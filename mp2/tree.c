/*

NAME: Anthony Gasbarro
Due: Feb 28 2018

//This program was edited to include a print post order function as well
//as a delete node function. This program will successfully print in postorder and
//will properly maintain tree order when deleting a node in any case.

 * EE 367 Machine Problem
 *
 * Author:  Galen Sasaki
 * Date:  Feb 5, 2018
 *
 * This program maintains a binary search tree that
 * can be manually changed by the user.  Here are
 * the commands:
 *   - (q) Quit
 *   - (e) Insert an alphabet
 *   - (d) Delete an alphabet
 *   - (t) List the nodes in the tree and their children
 *   - (i) List the nodes in in-order
 *   - (p) List the nodes in post-order
 *
 * The commands 'd' and 'p' do not work.
 * Your task is to make them work by implementing two functions:
 *   - deleteNode();
 *   - listPostOrder();
 *
 *  You can compile by "gcc tree.c"
 */

#include <stdio.h>
#include <stdlib.h>

struct node {
  char key;
  struct node *left, *right;
};

/* Creates and destroys nodes and trees */
struct node * createNode(char key);
void destroyNode(struct node * node);
void destroyTree(struct node * root);

/* insertNode and deleteNode will insert and delete nodes.  */
struct node * insertNode(struct node *node, char key);
struct node * deleteNode(struct node *node, char key);
struct node * minNode(struct node * node);

/* List the nodes in in-order and post-order */
void listInOrder(struct node * node);
void listPostOrder(struct node * node);

/* Displays a tree. */
void displayTree(struct node * root);

void main()
{

struct node * root = NULL;  /* Initialilze tree to empty */

printf("Welcome to the binary search tree!\n\n");

char key;
char cmd;
while(1) {
   printf("Commands \n");
   printf("     (q) Quit\n");
   printf("     (i) Insert a lower-case alphabet \n");
   printf("     (x) Delete a lower-case alphabet \n");
   printf("     (d) Display tree \n");
   printf("     (n) List nodes in-order\n");
   printf("     (p) List nodes post-order\n");

   printf("Enter command: ");
   cmd = getchar();
   while (getchar()!='\n');

   switch(cmd) {
	case 'q': /* Quit */
		destroyTree(root);
		return;
	case 'i': /* Insert key */
		printf("Enter char to insert ('a' - 'z'): ");
		key = getchar();
   		while (getchar()!='\n');
		root = insertNode(root, key);
		break;
	case 'x': /* Delete key */
		printf("Enter char to delete ('a' - 'z'): ");
		key = getchar();
   		while (getchar()!='\n');
		root = deleteNode(root, key);
		break;
	case 'd': /* Display tree */
		displayTree(root);
		break;
	case 'n': /* Display nodes in-order */
		printf("In-order list:");
		listInOrder(root);
		printf("\n");
		break;
	case 'p': /* Display nodes post-order */
		printf("Post-order list:");
		listPostOrder(root);
		printf("\n");
		break;
	default:
		printf("Invalid command, try again\n");
   }
}
}

struct node * createNode(char key)
{
struct node *p = (struct node *) malloc(sizeof(struct node));
p->left = NULL;
p->right = NULL;
p->key = key;
return p;
}

void destroyNode(struct node * node)
{
free(node);
}

void destroyTree(struct node * root)
{
if (root != NULL) {
	destroyTree(root->left);
	destroyTree(root->right);
	destroyNode(root);
}
}

/*
 * Fix this
 */
struct node * deleteNode(struct node * node, char key)
{

//create new pointer to traverse the trees
struct node *p = node;
//  printf("deleteNode is not implemented!!!\n");

//if the tree is empty do nothing
if (p == NULL)
    {return p;}

//if the key is smaller than the current node's, recursively traverse left
    if(key < p->key){
      p->left = deleteNode(p->left, key);
    }
//if the key is larger than the current node's recursively traverse right
    else if (key > p->key){
      p->right = deleteNode(p->right, key);
    }

//in the case that the key is equal to the current node
    else{
      //if there is no child to the left,
      // replace the current node with the right child
      // and return the current location
      if(p->left == NULL){
          struct node *temp = p->right;
          free (p);
          return temp;
      }
      //if there is no child to the right,
      // replace the current node with the left child
      // and return the current location
      else if(p->right == NULL){
        struct node *temp = p->left;
        free(p);
        return temp;
      }
      //if there are two children for the nodes
      //create a temp node that is the minimum of the right child
      //set the current node's key to the right child's
      //and recurse down the right child path to replace nodes accordingly
      struct node *temp = minNode(p->right);
      p->key = temp->key;
      p->right = deleteNode(p->right, temp->key);


    }
//return to main function
return node;
}


struct node * minNode(struct node * node){
  struct node * curr = node;
  while(curr->left != NULL){
    curr = curr->left;
  }
  return curr;
}

void listInOrder(struct node * node)
{
if (node != NULL) {
	listInOrder(node->left);
	printf(" %c ",node->key);
	listInOrder(node->right);
}
}

/*
 * Fix this
 */

//This function will recursively make calls to itself to iterate all the
//way down the left leg of the tree until the bottom is hit
//it will then work its way down to the right until it hits the bottom
//then move over one branch and repeat the process iterating to the left then right
//until the entire tree has been traversed and printed in post order


void listPostOrder(struct node * node)
{
//printf("listPostOrder is not implemented!!!\n");

//return to last iteration of recursive call if a leaf is found
if (node == NULL)
        {return;}

        //Recursive call on left child
        listPostOrder(node->left);
        //Recursive call on right child
        listPostOrder(node->right);

  //print value held at node
  printf("%c ", node->key);

}

struct node * insertNode(struct node * node, char key)
{
if (node == NULL) {
	return createNode(key);
}
if (node->key == key) {  /* Do nothing since key is already there */
	return node;
}
else if (key < node->key) {
	node->left = insertNode(node->left, key);
	return node;
}
else {
	node->right = insertNode(node->right, key);
	return node;
}
}

void displayTree(struct node * node)
{
if (node == NULL) {
	return;
}
printf("Node %c: ", node->key);
printf("Children[ ");
if (node->left == NULL) {
	printf("/");
}
else {
	printf("%c", node->left->key);
}
printf(", ");
if (node->right == NULL) {
	printf("/");
}
else {
	printf("%c", node->right->key);
}
printf(" ]\n");
displayTree(node->left);
displayTree(node->right);
}
