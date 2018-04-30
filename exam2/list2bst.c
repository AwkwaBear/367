//EE367 Midterm 2

//Completed By: Anthony Gasbarro
//Due April 6 2018

/*
 * Create a minimum height binary search tree from sorted nodes that
 * are in an array.
 */
#include <stdio.h>
#include <stdlib.h>

struct node {
	int key;
	struct node * left;
	struct node * right;
};

struct node ** create_nodes(int size);
void destroy_nodes(struct node **node_list, int size);
struct node * build_tree(struct node ** node_list, int size);
struct node * recursive_bst(struct node ** node_list, int start, int end);
int height(struct node *root);
void in_order(struct node *root);

void main(int argc, char * argv[])
{
if (argc != 2) {
	printf("Usage: ./a.out <number of data>\n");
}
int size = atoi(argv[1]);
printf("Size = %d\n", size);

struct node **node_list = create_nodes(size);

struct node *root = build_tree(node_list, size);

printf("Height of tree: %d\n", height(root));
printf("In-order listing of nodes in BST:\n");
in_order(root);
printf("\n");

destroy_nodes(node_list, size);
return;
}

struct node * build_tree(struct node ** node_list, int size)
{

//Establish start and for input to recursive call
int start = 0;
int end = size - 1;

//Begin recursive fucntion call with whole array and return root to main
return recursive_bst(node_list, start, end);


}

//This function will set the root of the tree to the midpoint of the build_tree
//then will recurse down the left and right side of the tree using midpoints to
//set each parent node along the way until a leaf is reached
//the result is a balanced BST
struct node * recursive_bst(struct node ** node_list, int start, int end){

//Base Case
if(start > end){
	return NULL;
}

//Find midpoint in array
int mid = (start + end) / 2;

//Create a root node or next node as recursing through depth of tree
struct node * root = node_list[mid];

//recursive call to create left child
root->left = recursive_bst(node_list, start, mid - 1);
//recursive call to create right child
root->right = recursive_bst(node_list, mid + 1, end);

//return root of BST to parent function
return root;

}

int height(struct node *root)
{
if (root == NULL) return 0;
int h_left = height(root->left);
int h_right = height(root->right);
if (h_left > h_right) return (h_left + 1);
else return (h_right + 1);
}

void in_order(struct node *root)
{
if (root == NULL) return;
in_order(root->left);
printf("%d ", root->key);
in_order(root->right);
}


struct node ** create_nodes(int size)
{
struct node **node_list = (struct node **)malloc(size*sizeof(struct node *));
for (int i=0; i<size; i++) {
	node_list[i] = (struct node *)malloc(sizeof(struct node));
	node_list[i]->key = i;
	node_list[i]->left = NULL;
	node_list[i]->right = NULL;
}
return node_list;
}

void destroy_nodes(struct node **node_list, int size)
{
for (int i=0; i<size; i++) {
	free(node_list[i]);
}
free(node_list);
}
