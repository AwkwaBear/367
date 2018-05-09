//Completed By: Anthony Gasbarro
//Due May 4th 2018

//This program will read in a Huffman Encoded file and decode it back to its original Format

#define NUMNODES 256

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
struct trie_node ** create_trie_node_array(int treecode[], int size);
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

//get convert binary to decimal function
int get_n(int str[], int length);

char ascii_convert(int str[], int length);

void main(int argc, char *argv[])
{
if (argc != 3) {
	printf("Usage:  ./decode367 <input compressed file> <output decompressed file>\n");
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

int str[12];

//get first 12 bits and convert to integer

for(int i = 11; i >= 0; i--){

		char c = fgetc(in_fp);
		if (c == '1'){
		str[i] = 1;
		}
		else if (c == '0'){
			str[i] = 0;
		}
		printf("c = %c\n", c);
	}


int n = get_n(str, 12);
printf("n = %d\n", n);
int treecode[n];

	for (int i = 0; i < n; i++){
		char c = fgetc(in_fp);
		if (c == '1'){
		treecode[i] = 1;
		}
		else if (c == '0'){
		treecode[i] = 0;
		}
printf("treecode %d: = %d\n", i, treecode[i]);
	}

struct trie_node ** forest = create_trie_node_array(treecode, n);
printf("tree node array returned\n");
printf("attempting to print keys\n");

for(int i = 0; i < n; i++){

	if(forest[i]->isleaf == TRUE){
	printf("key is %c", forest[i]->key);
}
}



} //end main

int get_n(int str[], int length){
	int n = 0;
	int mult = 1;

for (int i = 0; i < length; i++){
		if(i == 0 && str[i] == 1){
			n++;
		}
		if (i >= 1 && str[i] == 1){
			n = n + mult;
		}
		mult = mult*2;
	}
//	printf("n before return = %d", n);
	return n;
}


/*
struct trie_node * rebuild_huffman_trie(int treecode[], int size)
{
	struct trie_node * root = create_trie_nonleaf();

while (size > 1)

for(int i = 0; i < n; i++){
	if (treecode[i] == 1){
		create_trie_node()

	}
}

sort_priority_queue(queue, size);


// commented out debug
for(int i = 0; i < size; i++){
	printf("letter is %c freq is %d\n", queue[i]->key,queue[i]->freq);
}


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

*/
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


struct trie_node ** create_trie_node_array(int treecode[], int size)
{
struct trie_node ** trie_array =
	(struct trie_node **) malloc(size * sizeof(struct trie_node *));

for (int i=0; i <size; i++) { /* Initialize array */
	trie_array[i] = NULL;
}

for (int i=0; i<size; i++) { /* Collect statistics */
	int str[8];
	char data;
	int k = 0;
printf("loop i = %d\n", i);
	if (treecode[i] == 1) {
		trie_array[i] = create_trie_nonleaf();
	}
	else if(treecode[i] == 0){
		for(int j = 8; j >= 1; j--){
			str[k] = treecode[i+j];
			printf("input = %d\n", str[k]);
			k++;
		}
		data = ascii_convert(str, 8);
		printf("data = %c\n", data);
		printf("creating tree leaf\n");
		trie_array[i] = create_trie_leaf(data);
		printf("last tree leaf made\n");
		i += 8;
	}
}
return trie_array;
}

char ascii_convert(int str[], int length){
	int dec = get_n(str, length);
	printf("decimal = %d\n", dec);
	char c = (char) dec;
	printf("converted value is %c\n", c);
	return c;
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
