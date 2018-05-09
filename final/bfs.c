//FINAL EXAM EE 367

//Completed by: Anthony Gasbarro


/*
 * Breadth First Search algorithm to find shortest paths from
 * the source node 0 to all the other nodes.
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>


struct adjlist_node {
	int node;
	struct adjlist_node * next;
};

//struct of bfs nodes to store if node was visited
//
struct bfs_node{
	int pred;
	int visited;
};

int dequeue(int queue[], int num_nodes);

void enqueue(int queue[], int index, int num_nodes);

void bfs(struct adjlist_node ** adjlist, int num_nodes);

void displaypath(struct bfs_node ** paths, int current);

void main(int argc, char * argv[])
{
if (argc != 2) {
	printf("Usage:  ./a.out <input file name>\n");
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
int end_node0, end_node1;
struct adjlist_node * newnode;
for (int i=0; i<num_links; i++) {
	fscanf(fp, "%d %d ", &end_node0, &end_node1);

	newnode = (struct adjlist_node *) malloc(sizeof(struct adjlist_node *));
	newnode->node = end_node1;
	newnode->next = adjlist[end_node0];
	adjlist[end_node0] = newnode;

	newnode = (struct adjlist_node *) malloc(sizeof(struct adjlist_node *));
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
		printf("-> %d ", current->node);
	}
	printf("\n");
}
printf("\n");

bfs(adjlist, num_nodes);

fclose(fp);
return;
}

/*
 * The following function 'bfs' doesn't work.  It should compute
 * shortest paths from source node 0 to all other nodes, and dispslay
 * the paths.  Here the path length is the number of hops.
 * The input adjlist is the adjacency list, and num_nodes is the
 * number of nodes.
 */
void bfs(struct adjlist_node ** adjlist, int num_nodes)
{

//declare an array of nodes for the queue
int queue[num_nodes+1];

//initialize array to have all false values(-1)
//(queue will be empty)
for (int i=0; i<num_nodes+1; i++) {
	queue[i] = -1;
}


//dummy node for creation of paths array
struct bfs_node * node;

//declare an array for tracking shortest paths
struct bfs_node ** paths = (struct bfs_node **)
	malloc(sizeof(struct bfs_node *) * num_nodes+1);

//initiailize array to track paths and visited nodes
for (int i=0; i<num_nodes; i++) {
	node = (struct bfs_node *) malloc(sizeof(struct bfs_node *));
	node->visited = 0;
	node->pred = -1;
	paths[i] = node;

}


//mark first node as visited(flag value to 1) and
//enqueue it
paths[0]->visited = 1;
enqueue(queue, 0, num_nodes);



//declare index variable for use in main loop
//and set to source node 0
int index = 0;


//while loop for BFS will iterate until
//first value of queue = -1 (false index)
while(queue[0] != -1){//begin 'while'

	//pull node from queue to
	index = dequeue(queue, num_nodes);


		//for loop iterates through adjaceny list for the given index node
		for(struct adjlist_node * current = adjlist[index]; current != NULL;
				current = current->next){//begin 'for'

					//if next node has not been visited already
					if(paths[current->node]->visited == 0){//begin 'if'

								//mark node as visited, mark predecessor, enqueue next node
								paths[current->node]->visited = 1;
								paths[current->node]->pred = index;
								enqueue(queue, current->node, num_nodes);

							}//end 'if'
				}//end 'for'

}//end while 'loop'

printf("Shortest paths:\n");

for(int i = 1; i < num_nodes; i++){
	displaypath(paths, i);
	printf("\n");
}

}

void displaypath(struct bfs_node ** paths, int current){
	if(paths[current]->pred != -1){
		displaypath(paths, paths[current]->pred);
	}
	if(paths[current]->pred == -1){
		printf("0 ");
	}
	else{
	printf("-> %d ", current);
	}
	return;
}


int dequeue(int queue[], int num_nodes){

	int deq = queue[0];
	for(int i = 0; i <= num_nodes; i++){
		queue[i] = queue[i+1];
	}

	//reset last node to empty value
	queue[num_nodes+1] = -1;

	return deq;
}

void enqueue(int queue[], int index, int num_nodes){

		for(int i = 0; i <= num_nodes; i++){
			if(queue[i] == -1){
				queue[i] = index;
				break;
			}
		}

	//reset last node to NULL
		queue[num_nodes+1] = -1;

}
