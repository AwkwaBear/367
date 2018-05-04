//Completed By: Anthony Gasbarro
//Due May 4th 2018


/*
 * This program will input a data file and output a data compressed
 * file using the Huffman code.  The Huffman trie is included at the
 * beginning of the compressed file as follows
 *
 * Output File Format:
 * 	- First 12 bits: The size n of the compressed Huffman trie
 * 	     represented as a 12-bit binary number
 * 	- Next n bits:  The compressed Huffman trie
 * 	     This is the pre-order of the Huffman trie
 * 	     1: means a nonleaf node
 * 	     0: means a leaf node,
 * 	          this is followed by the 8-bit representation of the
 * 	          data byte for the leaf.
 * 	- The rest of the bits:  The compressed data
 *
 *  Usage:  ./encode367 <input data file> <output compressed file>
 *  Assumes the executable code is named 'encode367'
 *
 *  The output file has each bit represented by an ASCII '0' or '1'.
 *  This will make it easier to debug, e.g., when viewing your output.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUMNODES 256

enum boolean {TRUE, FALSE};

struct trie_node {
	struct trie_node *child[2];
	enum boolean isleaf;  /* Is the node a leaf? */
	char key;             /* Data byte if this is a leaf */
	char *codeword;                /* Codeword */
	unsigned int codeword_length;  /* Length of codeword */
	unsigned int freq;    /* Frequency of data byte in data file */
};

/*
 * Building and destroying different trie nodes
 * create_trie_node is the generic version, where as
 *     create_trie_leaf will create leaf nodes
 *     create_trie_nonleaf will create nonleaf nodes
 */
struct trie_node * create_trie_leaf(char key);
struct trie_node * create_trie_nonleaf();
struct trie_node * create_trie_node(enum boolean isleaf, char key);
void destroy_trie_node(struct trie_node * node);

/*
 * Creates and destroys an array to store trie leaves (which have data bytes)
 * This can be used to look up trie leaves based on data byte values
 */
struct trie_node ** create_trie_node_array(FILE *fp);
void destroy_trie_node_array(struct trie_node ** trie_node_array);

/* Computes the number of data bytes in a trie leaf array */
int num_symbols(struct trie_node ** trie_node_array);

/* Converts an int value to a binary string, represented by a char string */
void int_to_binary(int n, char str[], int length);

/* Displays a char string */
void display_binary(char str[], int length);

/* Build a Huffman trie from a trie leaf array, and destroy it */
struct trie_node * build_huffman_trie(struct trie_node * trie_node_array[]);
void destroy_huffman_trie(struct trie_node * root);

/* Computes codewords in a Huffman trie */
void build_codewords(struct trie_node * root);

/* Calculates the size of the encoded data file */
int encoded_data_size(struct trie_node * root);

/*
 * Displays the trie - useful for debugging.
 *    Don't delete this function, though you can delete any calls to it.
 */
void debug_display_trie(struct trie_node * root);

//functions to update priority queue
void sort_priority_queue(struct trie_node ** queue, int size);

void swap_nodes(struct trie_node * px, struct trie_node *py);

struct trie_node * extract_min(struct trie_node ** queue,int size);

void add_priority_queue(struct trie_node * treeroot,struct trie_node ** queue, int size);

//function to encode tree
void encode_tree(struct trie_node * root, FILE * out_fp);


void post_ordertraverse(struct trie_node* node, FILE * out_fp);

void compress_file(struct trie_node* node, FILE * in_fp, FILE * out_fp);

void search_tree(int x, struct trie_node* node, FILE * out_fp);

void write_codeword(char * codeword, FILE * out_fp);

void main(int argc, char *argv[])
{
if (argc != 3) {
	printf("Usage:  ./encode367 <input file> <output compressed file>\n");
	exit(EXIT_FAILURE);
}

if (access(argv[2],F_OK)==0) {
	printf("Do you want to overwrite '%s' (y/n): ", argv[2]);
	char c = getchar();
	if (c != 'y') exit(EXIT_SUCCESS);
}

FILE *in_fp = fopen(argv[1], "r");
if (in_fp == NULL) {
	printf("Can't open file %s\n", argv[1]);
	exit(EXIT_FAILURE);
}

FILE *out_fp = fopen(argv[2], "w");
if (out_fp == NULL) {
	printf("Can't open file %s\n", argv[2]);
	exit(EXIT_FAILURE);
}

/* Array for trie leaf nodes, which have data bytes */
struct trie_node **trie_array = create_trie_node_array(in_fp);
rewind(in_fp); /* Resets the file position to the begining of the file */

int num_leaves = num_symbols(trie_array);
int num_nonleaves = num_leaves-1;
int encoded_trie_size = num_leaves*9 + num_nonleaves;
printf("Number of leaves in the trie: %d\n", num_leaves);
printf("Size of encoded trie: %d\n", encoded_trie_size);
char str[12];
int_to_binary(encoded_trie_size, str, 12);
printf("12-bit binary representation of %d: ", encoded_trie_size);
display_binary(str, 12);
printf("\n");

if (num_leaves < 2) {
	printf("Number of symbols in file %s is less than 2!\n",argv[1]);
	exit(EXIT_FAILURE);
}
/* Build trie */
struct trie_node *root = build_huffman_trie(trie_array);

/* Compute codewords */
build_codewords(root);

/* Display sizes of encoded data and the encoded file */
int n = encoded_data_size(root);
printf("Size of encoded data: %d\n", n);
printf("Size of encoded file: %d\n", 12 + encoded_trie_size + n);

/* Display trie -- this is for debugging and this call can be deleted */
debug_display_trie(root);

int_to_binary(n, str, 12);
for (int i=0; i<12; i++) {
 fprintf(out_fp,"%c", str[11-i]);
}

encode_tree(root,out_fp);

compress_file(root,in_fp, out_fp);

printf("\n");

/*
 * Free unused memory
 */
destroy_huffman_trie(root);
destroy_trie_node_array(trie_array);

fclose(in_fp);
fclose(out_fp);

exit(EXIT_SUCCESS);
}



struct trie_node * build_huffman_trie(struct trie_node * trie_array[])
{
struct trie_node * queue[NUMNODES];
struct trie_node * treeroot;
int head = 0;
int tail = NUMNODES-1;
int size = 0;

for (int i=0; i<NUMNODES; i++) {
	if (trie_array[i] != NULL) {
		if (trie_array[i]->isleaf == TRUE) {
			tail = (tail+1)%NUMNODES;
			queue[tail] = trie_array[i];
			size++;
		}
	}
}

sort_priority_queue(queue, size);


/* commented out debug
for(int i = 0; i < size; i++){
	printf("letter is %c freq is %d\n", queue[i]->key,queue[i]->freq);
}
*/

while(size > 1) {
	struct trie_node * new_node = create_trie_nonleaf();

	for (int k=0; k<2; k++) {
		new_node->child[k] = extract_min(queue, size);
		size--;
		new_node->freq += new_node->child[k]->freq;
	}

	treeroot = new_node;
	add_priority_queue(treeroot, queue, size);
	size++;

	sort_priority_queue(queue, size);
}

return treeroot;
}


void sort_priority_queue(struct trie_node ** queue, int size){
	for(int i = 0; i < size-1; i++){
		for(int j = 0; j < size-i-1; j++){
			if (queue[j]->freq > queue[j+1]->freq)
              swap_nodes(queue[j], queue[j+1]);
		}
	}
}

void swap_nodes(struct trie_node * px, struct trie_node *py){
	struct trie_node temp =  *px;
	*px = *py;
	*py = temp;
}

void add_priority_queue(struct trie_node * treeroot,struct trie_node ** queue, int size){
	for(int i = size; i >= 0; i--){
		queue[i+1] = queue[i];
	}
	queue[0] = treeroot;
}

//will remove lowest freq node from queue and return it
struct trie_node * extract_min(struct trie_node ** queue, int size){
	struct trie_node *temp = queue[0];

	for(int i = 0; i < size; i++){
		queue[i] = queue[i+1];
	}

 	return temp;
}

void destroy_huffman_trie(struct trie_node * root)
{
if (root==NULL) return;
if (root->isleaf == TRUE) {
	for (int i=0; i<2; i++) {
		destroy_huffman_trie(root->child[i]);
	}
}
free(root->codeword);
free(root);
return;
}

void encode_tree(struct trie_node * root, FILE * out_fp){
	post_ordertraverse(root, out_fp);
}

void post_ordertraverse(struct trie_node* node, FILE * out_fp)
{
    if (node == NULL)
          return;

    if(node->isleaf == FALSE){
     fprintf(out_fp,"1");
 	 }
	 else {
		 int temp = (int) node->key;
		 char str[12];
		 int_to_binary(temp, str, 12);
		 fprintf(out_fp, "0");
		 for (int i=0; i<12; i++) {
		 	fprintf(out_fp,"%c", str[11-i]);
		 }
	 }
     /* then recur on left sutree */
     post_ordertraverse(node->child[0],out_fp);

     /* now recur on right subtree */
    post_ordertraverse(node->child[1], out_fp);
}

//file read in and encoding function
void compress_file(struct trie_node* node, FILE * in_fp, FILE * out_fp){
	rewind(in_fp);
	for (int x=fgetc(in_fp); x!=EOF; x=fgetc(in_fp)) {
			search_tree(x, node, out_fp);
		}
}

//search tree recurses whole tree to find character to print
void search_tree(int x, struct trie_node* node, FILE * out_fp)
{
    if (node == NULL)
          return;

		if(x == node->key){
			for (int k=0; k < node->codeword_length; k++) {
				fprintf(out_fp,"%c",node->codeword[node->codeword_length-1-k]);
			}
		}
     /* then recur on left sutree */
     search_tree(x ,node->child[0],out_fp);

     /* now recur on right subtree */
    search_tree(x,node->child[1], out_fp);
}

/*
 * Calculate the size of the encoded data file
 */
int encoded_data_size(struct trie_node * root)
{
if (root->isleaf == TRUE) {
	return root->freq*root->codeword_length;
}
else {
	return encoded_data_size(root->child[0])
		+ encoded_data_size(root->child[1]);
}
}

/*
 * Compute codewords in a Huffman trie - recursive version
 */

void build_codewords_rec(struct trie_node * root, char path[], int depth)
{
	if (root->isleaf == TRUE) { /* Compute codeword */
		root->codeword_length = depth;
		root->codeword = (char *) malloc(depth*sizeof(char));
		for (int i=0; i<depth; i++) {
			root->codeword[depth-1-i] = path[i];
		}
	}
	else {  /* Nonleaf node */
		for (int k=0; k<2; k++) {
			path[depth] = '0'+k;
			build_codewords_rec(root->child[k], path, depth+1);
		}
	}
}

/*
 * Compute codewords in a Huffman trie
 */

void build_codewords(struct trie_node * root)
{
char path[NUMNODES];
int depth = 0;

build_codewords_rec(root, path, 0);
}

/*
 * Build and destroy trie nodes
 * create_trie_node is the generic version, whereas
 *     create_trie_leaf will create leaf nodes
 *     create_trie_nonleaf will create nonleaf nodes
 */

struct trie_node * create_trie_leaf(char key)
{
return create_trie_node(TRUE, key);
}

struct trie_node * create_trie_nonleaf()
{
return create_trie_node(FALSE, (char) 0);
}

struct trie_node * create_trie_node(enum boolean isleaf, char key)
{
struct trie_node *node =
	(struct trie_node *)malloc(sizeof(struct trie_node));
node->isleaf = isleaf;
node->key = key;
node->child[0] = NULL;
node->child[1] = NULL;
node->freq = 0;
node->codeword_length = 0;

return node;
}

void destroy_trie_node(struct trie_node * node)
{
free(node->codeword);
free(node);
return;
}

/*
 * Create and destroy an array to store trie leaves (which have data bytes)
 * This can be used to look up trie leaves based on data byte values
 */

struct trie_node ** create_trie_node_array(FILE *fp)
{
struct trie_node ** trie_array =
	(struct trie_node **) malloc(NUMNODES * sizeof(struct trie_node *));

for (int i=0; i<NUMNODES; i++) { /* Initialize array */
	trie_array[i] = NULL;
}

for (int n=fgetc(fp); n!=EOF; n=fgetc(fp)) { /* Collect statistics */
	if (trie_array[n] == NULL) {
		trie_array[n] = create_trie_leaf((char) n);
		trie_array[n]->freq = 1;
	}
	else {
		trie_array[n]->freq++;
	}
}

return trie_array;
}

void destroy_trie_node_array(struct trie_node ** trie_node_array)
{
for (int i=0; i<NUMNODES; i++) {
	if (trie_node_array[i] != NULL) {
		free(trie_node_array[i]->codeword);
	}
}
free(trie_node_array);

return;
}

/*
 * Compute the number of data bytes in a trie leaf array
 */

int num_symbols(struct trie_node ** trie_node_array)
{
int num = 0;
for (int i=0; i<NUMNODES; i++) {
	if (trie_node_array[i] != NULL) {
		num++;
	}
}
return num;
}

/*
 * Converts an int value to a binary string, represented by a char string
 */

void int_to_binary(int n, char str[], int length)
{
int value = n;
for (int i=0; i<length; i++) {
	str[i] = '0' + (value%2);
	value = value>>1;
}
}

/*
 * Displays a char string
 */

void display_binary(char str[], int length)
{
for (int i=0; i<length; i++) {
	printf("%c", str[length-1-i]);
}
}

/*
 * Recursive version of 'debug_display'.  Used in debugging.
 * Do not delete this function.
 */
void debug_display_trie_rec(struct trie_node * root, int depth)
{
for (int i=0; i<depth; i++) {
	printf("     ");
}
if (root->isleaf == FALSE) { /* Display nonleaf and children */
	printf("+ freq: %d\n", root->freq);
	for (int i=0; i<2; i++) {
		debug_display_trie_rec(root->child[i], depth+1);
	}
}
else {  /* Display a leaf */
	printf("> freq: %d key: %x(hex) codeword: ",
			root->freq, (unsigned int) root->key);
	for (int k=0; k<root->codeword_length; k++) {
		putchar(root->codeword[root->codeword_length-1-k]);
	}
	printf("\n");
}
}


/*
 * Displays the trie.  Used in debugging.  Do not delete this function
 */

void debug_display_trie(struct trie_node * root)
{
printf("Display trie:  + = Nonleaf     > = Leaf\n");
debug_display_trie_rec(root, 0);
}
