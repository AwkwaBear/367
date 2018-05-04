struct trie_node {
	struct trie_node *child[2];
	enum boolean isleaf;  /* Is the node a leaf? */
	char key;             /* Data byte if this is a leaf */
	char *codeword;                /* Codeword */
	unsigned int codeword_length;  /* Length of codeword */
	unsigned int freq;    /* Frequency of data byte in data file */
};

create_trie_node_array()
// generates array of 256 slots array[n] (as leaf nodes);
// int n = character of node in integer Form
// leaf nodes have made with
// isleaf = TRUE
// k = letter from text as char
// child[2] = NULL
// codeword_length = 0

num_leaves() = amount of slots filled in node Array
//number of leaves Used

non_leaves() = number of leaves - 1;
//one less than total num_leaves

encoded_trie_size() = num_leaves*9 + non_leaves;

int_to_binary() = encoded tree size in int_to_binary
//convert size of encoding to a 12-bit value

display_binary()
//print binary tree to screen in characters

build_huffman_trie()
//build tree function using array of leaf nodes

    queue() = array with all leaf_nodes



//Below is prototype functions
void priority_queue(struct ** trie_node queue, int size);
void swap_nodes(struct * trie_node x; struct * trie_node y);

void sort_priority_queue(struct ** trie_node queue, int tail){
	for(int i = 0; i < tail-1; i++){
		for(int j = 0; j < tail-i-1; j++){
			if (queue[j]->freq > queue[j+1]->freq)
              swap(&queue[j], &queue[j+1])
		}
	}
}

//will remove lowest freq node from queue and return it
struct trie_node * extract_min(struct trie_node ** queue, int size){
	struct trie_node *temp = queue[0];

	for(int i = 0; i < tail; i++){
		queue[i] = queue[i+1];
	}

 	return temp;
}


void swap_nodes(struct trie_node * px; struct trie_node *py){
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
/* *******ALGORITHM**********

1. Take in array and generate min-priority queue

2. merge 2 least frequent key's and generate new node that has the sum of their frequencies

3. repeat above for all nodes including newly generated node



pseudo code

huffman(C)
n = |C|   //num_leaves
Q = C    //min heap of nodes by frequency
for i = 1 to n-1
    node 'z' = make new "create_trie_nonleaf"
    z.left = x = EXTRACT MIN(Q) //smallest node goes on left
    z.right = y = EXTRACT MIN(Q) //nex smallest goes on right
    z.freq = x.freq + y.freq
    Insert (Q.z)
return Extract MIN (Q) //return tree root



min_heap
struct minheap{
struct trie_node * root;



};

struct heapnode {
struct trie_node * node;
struct heapnode *right;
struct heapnode *left
};





*/
void write_codeword(char * codeword, FILE * out_fp);

void write_codeword(char * codeword, FILE * out_fp){
	fprintf(out_fp, %c, out)
	for (int k=0; k<root->codeword_length; k++) {
		putchar(root->codeword[root->codeword_length-1-k]);
	}
}

void compress_file(strustruct trie_node* node, FILE * in_fp, FILE * out_fp){
	rewind(in_fp);
	for (int x=fgetc(in_fp); x!=EOF; x=fgetc(in_fp)) {
			search_tree(x, node, out_fp);
		}
}

void search_tree(int x, struct trie_node* node, FILE * out_fp)
{
    if (node == NULL)
          return;

		if(x == node->key){
			write_codeword(node->codeword, out_fp);
		}
     /* then recur on left sutree */
     search_tree(x ,node->child[0],out_fp);

     /* now recur on right subtree */
    search_tree(x,node->child[1], out_fp);
}

void post_ordertraverse(struct trie_node* node, FILE * out_fp){

     if (node == NULL)
          return;

    if(node->isleaf == FALSE){
     fprintf(out_fp,"[1]");
 	 }
	 else {
		 int temp = (int) node->key;
		 char str[12];
		 int_to_binary(temp, str, 12);
		 fprintf(out_fp, "[0, %d]", temp);
	 }
     /* then recur on left sutree */
     post_ordertraverse(node->child[0], FILE * out_fp);

     /* now recur on right subtree */
    post_ordertraverse(node->child[1], FILE * out_fp);
}
