/*
 * Bellman Ford algorithm
 */
#include <stdio.h>
#include <stdlib.h>

struct adjlist_node {
	int node;
	int weight;
	struct adjlist_node * next;
};

void bf(struct adjlist_node ** adjlist, int num_nodes);

void main(int argc, char * argv[])
{
if (argc != 2) {
	printf("Usage:  ./a.out <file name>\n");
	return;
}

FILE * fp = fopen(argv[1],"r");
if (fp == NULL) {
	printf("File '%s' didn't open\n", argv[1]);
	return;
}
int num_nodes;
fscanf(fp, "%d", &num_nodes);

/* Create adjacency list */
struct adjlist_node ** adjlist = (struct adjlist_node **) 
	malloc(sizeof(struct adjlist_node *)*num_nodes);
for (int i=0; i<num_nodes; i++) {
	adjlist[i] = NULL;
}	

int num_links;
fscanf(fp, "%d", &num_links);
int end_node0, end_node1, weight;
struct adjlist_node * newnode;
for (int i=0; i<num_links; i++) {
	fscanf(fp, "%d %d %d", &end_node0, &end_node1, &weight);

	newnode = (struct adjlist_node *) malloc(sizeof(struct adjlist_node *));
	newnode->weight = weight;
	newnode->node = end_node1;
	newnode->next = adjlist[end_node0];
	adjlist[end_node0] = newnode;

	newnode = (struct adjlist_node *) malloc(sizeof(struct adjlist_node *));
	newnode->weight = weight;
	newnode->node = end_node0;
	newnode->next = adjlist[end_node1];	
	adjlist[end_node1] = newnode;
}

/* Display the adjacency list */
printf("Adjacency list:\n");
for (int i=0; i<num_nodes; i++) {
	printf("Node %d:", i);
	for (struct adjlist_node * current = adjlist[i]; current != NULL;
			current = current->next) {
		printf("-> [node=%d wt=%d]", current->node, current->weight);
	}
	printf("\n");
}

bf(adjlist, num_nodes);

fclose(fp);
return;
}

/*
 * The following function 'bf' doesn't work.  It should compute
 * shortest paths from node 0 to all other nodes, and dispslay
 * the paths.
 * The input adjlist is the adjacency list, and num_nodes is the
 * number of nodes.
 */
void bf(struct adjlist_node ** adjlist, int num_nodes)
{
printf("Function 'bf' doesn't work!\n");
printf("Shortest paths:\n");

}

