/*
 * Bellman Ford algorithm
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


struct adjlist_node {
	int node;
	int weight;
	struct adjlist_node * next;
};

void printpath(int parent[], int v);

void bf(struct adjlist_node ** adjlist, int n, int e);

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

bf(adjlist, num_nodes, num_links);

fclose(fp);
return;
}


//Function to print paths from source to vertex
//function recursively calls itself to print path via
//following parents of each node
void printpath(int parent[], int v){//begin function
	if (v < 0){//begin if
		return;
		}//end if

	printpath(parent, parent[v]);
	printf("%d ->", v);

}//end function

/*
 * The following function 'bf' doesn't work.  It should compute
 * shortest paths from node 0 to all other nodes, and dispslay
 * the paths.
 * The input adjlist is the adjacency list, and num_nodes is the
 * number of nodes.
 */
void bf(struct adjlist_node ** adjlist, int n, int e){//begin function

int source;
	//Set Source node to node 0 in graph
	for (int i = 0; i < n-1; i++){
		if (adjlist[i]->next == 0){
			source = i;
			printf("source set to %d", i);
		}
	}

	//variables u,v,w will store node, next, weight respectively
	int u, v, w;

	//k is a counter variable set to n
	int k = n;

	//Distance and parent store least cost path info
	//source vertex has no cost and no parent all others have infinity
	int distance[n];
	int parent[n];

	//set current node to first node in list
	struct adjlist_node * current = adjlist[source];

	//Initialize distance array to infinity
	for(int i = 0; i < n; i++){
		distance[i] = INT_MAX;
	}
	//Set source node distance to 0
	distance[source] = 0;

	//Initialize parent array to -1
	for(int i = 0; i < n; i++){
		parent[i] = -1;
//		printf("parent set to -1 \n");
	}

	//Relaxation of edges occurs in this loop
	for (int i = 0; i < n-1 ; i++){//begin for '1'

		//reinitialize current for each loop iteration
		current = adjlist[source];

	while(current != NULL){//begin while '1'

			printf("for loop iteration %d\n", i);
			//Set u,v,w to current nodes' values
			u = current->node;
			printf("current node is %d\n", u);

			if(current->next != NULL){
			v = current->next->node;
			printf("next node is %d\n", v);
			}

			w = current->weight;
			printf("edge weigh is %d\n", w);

			if(distance[u] + w < distance[v]){//begin if '1'

				//new lowest distance is updated
				distance[v] = distance[u] + w;
				printf("distance set %d\n", distance[v]);

				//parent of 'v' set to 'u'
				parent[v] = u;
				printf("parent set %d\n", parent[v]);
			}//end if '1'


//			else if(distance[u] + w == distance[v]){//begin elsif '1'
//			parent[v] = u;




			current = current->next;
		}//end while '1'

	}//end for




	//Run relaxation again once more for nth time to check for negative weight cycles


//reinitialize current while loop
		current = adjlist[source];

	while(current != NULL){//begin while '1'

//			printf("for loop iteration %d\n", i);
			//Set u,v,w to current nodes' values
			u = current->node;
			printf("current node is %d\n", u);

			if(current->next != NULL){
			v = current->next->node;
			printf("next node is %d\n", v);
			}

			w = current->weight;
			printf("edge weigh is %d\n", w);

			if(distance[u] + w < distance[v]){//begin if '1'
			printf("ERROR: Graph contains negative-weight cycle\n");


			}//end if '1'


			current = current->next;
		}//end while '1'






	printf("Shortest paths:\n");
	current = adjlist[source];
	int i = 0;
	while(current != NULL){

		printpath(parent, i);
		printf("\n");
		i++;
	}



}//end function
