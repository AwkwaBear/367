
//Name: Anthony Gasbarro

/*
 * Implement "reverse_tree" and "common".
 */
#include <stdio.h>
#include <stdlib.h>
struct node {
   char           key;
   struct node * left;
   struct node * right;
};


void reverse_tree(struct node * x);
struct node * common(struct node * root, char c0, char c1);
//function added to search tree for values

int search(struct node * root, char c);

/* Loads data from a file and returns a tree */
struct node * load_data(FILE *fp);
struct node * create_node(char c);

/* The next two functions displays the tree */
void display_tree(struct node * root);
void display_tree_recursive(struct node * node);


void main(int argc, char *argv[])
{
struct node * x;
int flag;
if (argc != 2) {
	printf("Usage:  .\a.out <data file>\n");
	return;
}
printf("Data file: %s\n",argv[1]);

FILE *fp = fopen(argv[1], "r");
if (fp == NULL) {
	printf("File '%s' does not exist\n",argv[1]);
	return;
}

struct node *root =load_data(fp);
printf("Loaded tree data:\n");
display_tree(root);

printf("Reverse tree:\n");
reverse_tree(root);
display_tree(root);

struct node *z;

//reverse_tree(root);

printf("Lowest common ancestor of 'x' and 'y' ");
z = common(root, 'x', 'y');
if ((flag = search(root,'x')) == 0 || (flag = search(root,'y')) == 0){
  z = NULL;
}
if (z == NULL) printf("does not exist\n");
else printf("is '%c'\n",z->key);

printf("Lowest common ancestor of 'b' and 'h' ");

z = common(root, 'b', 'h');
if ((flag = search(root,'b')) == 0 || (flag = search(root,'h')) == 0){
  z = NULL;
}
if (z == NULL) printf("does not exist\n");
else printf("is '%c'\n",z->key);

printf("Lowest common ancestor of 'x' and 'u' ");
z = common(root, 'x', 'u');
z = NULL;
if (z == NULL) printf("does not exist\n");
else printf("is '%c'\n",z->key);
}

/*
 * Implement this function.
 * It will reverse the binary tree rooted at x
 */
void reverse_tree(struct node * root)
{
  if (root == NULL){
    return;
  }
  else{
    reverse_tree(root->left);
    reverse_tree(root->right);
    struct node *temp = root->left;
    root->left = root->right;
    root->right = temp;
    return;
  }
}

int search(struct node * root,char c){
  if (root == NULL || c == root->key){

    return 1;
  }
  if(c < root->key){

    return search(root->left, c);
  }
  if(c > root->key){

    return search(root->right, c);
  }
  return 0;
}


/*
 * Implement this function
 * It will find the lowest common ancestor of nodes with keys c0 and c1.
 * It will return a pointer to the ancestor.
 * If there is no ancestor then it will return NULL
 */
struct node * common(struct node * root, char c0, char c1)
{

  if(!root){
      return NULL;
    }
  //If root is a given value then it is the LCA
  if(root->key == c0 || root->key == c1){
    return root;
  }
  //Most other cases will flow into the following case
  else{
//    printf("root is %c\n", root->key);

    //Search left subtree for LCA
    struct node *left = common(root->left, c0, c1);
    //Search right subtree for LCA
    struct node *right = common(root->right, c0, c1);
    //if node us found in left and right then root is LCA
    if (left && right){
      return root;
    }
    //if one node is found in either left or right it is the LCA
    if(left){
      return left;
    }
    if(right){
      return right;
    }

  }
}



void display_tree(struct node * root)
{
if (root==NULL) return;
display_tree_recursive(root);
}

void display_tree_recursive(struct node * node)
{

if (node == NULL) return;

printf("%c: ",node->key);  // Print node

if (node->left == NULL) printf("/ "); // Print left child
else printf("%c ",node->left->key);

if (node->right == NULL) printf("/\n"); // Print right child
else printf("%c\n",node->right->key);

display_tree_recursive(node->left);
display_tree_recursive(node->right);
}

struct node * load_data(FILE *fp)
{

struct node *head;
int valid[256];        // Indicates if character i is valid
struct node * nodeptr[256];  // Points to nodes
char left_child[256];
char right_child[256];

for (int i=0; i<256; i++) valid[i]=0;

int num_nodes;
char current, left, right;
int root;
fscanf(fp, "%d\n", &num_nodes);

for (int i=0; i<num_nodes; i++) {  /* Load tree data from file */
	fscanf(fp,"%c %c %c\n",&current, &left, &right);
	if (i==0) root = (int) current;
	int k = (int) current;
	valid[k] = 1;
	nodeptr[k] = create_node(current);
	left_child[k] = left;
	right_child[k] = right;
}

for (int i=0; i<256; i++) { /* Create tree */
	if (valid[i] == 1) {
		if (left_child[i] != '/') {
			if (valid[left_child[i]] == 1) {
				nodeptr[i]->left = nodeptr[left_child[i]];
			}
			else {
				printf("Data file has an error for node %c\n",
					left_child[i]);
				return NULL;
			}
		}
		if (right_child[i] != '/') {
			if (valid[right_child[i]] == 1) {
				nodeptr[i]->right = nodeptr[right_child[i]];
			}
			else {
				printf("Data file has an error for node %c\n",
					right_child[i]);
				return NULL;
			}
		}
	}
}

return nodeptr[root];
}

struct node * create_node(char c)
{
struct node * x = (struct node *) malloc(sizeof(struct node));

x->left = NULL;
x->right = NULL;
x->key = c;
return x;
}
