//Sebastian Medina                 CruzID: Seamedin         Course: CSE 101
//December 5, 2019                 FIlename: Graph.c
//Description: Graph ADT implementation

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

//Colors
#define W -1
#define Gr 0
#define B 1


void Visit(Graph G, List S, int u, int *time);

typedef struct GraphObj{
	int source;		//Most recently used source by DFS 
	int order;		//# of vertices
	int size;		//# of edges
	int* c;			//color
	int* d;			//discover
	int* f;			//finish
	int* p;			//parent

	List *adjacentVert;
}GraphObj;

/* Constructors-Destructors */

// creates new graph
Graph newGraph(int n){
	Graph G = malloc(sizeof(GraphObj));

	G->source = NIL;
	G->order = n;
	G->size = 0;

	G->c = calloc(n+1, sizeof(int));
	G->d = calloc(n+1, sizeof(int));
	G->f = calloc(n+1, sizeof(int));
	G->p = calloc(n+1, sizeof(int));

	G->adjacentVert = calloc(n+1, sizeof(List));

	for(int i = 0; i <= n; i++){
		G->c[i] = W;
		G->d[i] = UNDEF;
		G->f[i] = UNDEF;
		G->p[i] = NIL;

		G->adjacentVert[i] = newList();
	}

	return G;
}

// free's graph from memory
void freeGraph(Graph* pG){
	if(*pG == NULL){
        printf("Graph Error: Cannot call freeGraph() on an empty Graph\n");
        exit(EXIT_FAILURE);
    }

    Graph toFree = *pG;
    for(int i = 0; i <= toFree->order; i++){
        freeList(&toFree->adjacentVert[i]);
    }

    free(toFree->c); free(toFree->d); free(toFree->p);
    free(toFree->f);
    free(toFree->adjacentVert);

    free(*pG);
    *pG = NULL;
}

/* Access functions */

// returns the # of vertices
int getOrder(Graph G){
	if(G == NULL){
 		printf("Graph Error: Cannot call getOrder() on an empty Graph\n");
 		exit(EXIT_FAILURE);
 	}

	return G->order;
}

// returns # of edges
int getSize(Graph G){
	if(G == NULL){
 		printf("Graph Error: Cannot call getSize() on an empty Graph\n");
 		exit(EXIT_FAILURE);
 	}

	return G->size;
}

// returns parent of vertex
/* Pre: 1<=u<=n=getOrder(G) */
int getParent(Graph G, int u){
	if(G == NULL){
 		printf("Graph Error: Cannot call getParent() on an empty Graph\n");
 		exit(EXIT_FAILURE);
 	}

 	if(1 > u || u > getOrder(G)){
 		printf("Graph Error: Cannot call getParent() on out of bounds value\n");
 		exit(EXIT_FAILURE);
 	}

	return G->p[u];
}

// returns discover time of vertex
/* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u){
	if(G == NULL){
 		printf("Graph Error: Cannot call getParent() on an empty Graph\n");
 		exit(EXIT_FAILURE);
 	}

 	if(1 > u || u > getOrder(G)){
 		printf("Graph Error: Cannot call getParent() on out of bounds value\n");
 		exit(EXIT_FAILURE);
 	}

 	return G->d[u];
}

// returns finish time of vertex
/* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u){
	if(G == NULL){
 		printf("Graph Error: Cannot call getParent() on an empty Graph\n");
 		exit(EXIT_FAILURE);
 	}

 	if(1 > u || u > getOrder(G)){
 		printf("Graph Error: Cannot call getParent() on out of bounds value\n");
 		exit(EXIT_FAILURE);
 	}

 	return G->f[u];
} 

/* Manipulation procedures */

// inserts a new directed edge from u to v
// i.e. v is added to the adjacency List of u
/* Pre: 1<=u<=n, 1<=v<=n */
void addArc(Graph G, int u, int v){
	if(G == NULL){
        printf("Graph Error: Cannot call addArc() on an empty Graph\n");
 		exit(EXIT_FAILURE);
    }

    if(u < 1 || u > getOrder(G)){
        printf("Graph Error: Cannot call addArc() with out of bounds value 'u'\n");
 		exit(EXIT_FAILURE);
    }

    if(v < 1 || v > getOrder(G)){
        printf("Graph Error: Cannot call addArc() with out of bounds value 'v'\n");
 		exit(EXIT_FAILURE);
    }

    // adjacency list of 'u'
    List lG = G->adjacentVert[u];

    //if list is empty
    if (length(lG) == 0){
    	append(lG, v);
    }
    else {
    	moveFront(lG);

    	while(index(lG) >= 0){
    		if(v < get(lG)){
    			insertBefore(lG,v);
    			break;
    		}
    		else if(lG->cursor->moveNext == NULL){
    			append(lG, v);
    			break;
    		}
    		moveNext(lG);
    	}
    }
    G->size++;
}


// inserts a new edge joining u to v, i.e. u is added to the adjacency List
/* Pre: 1<=u<=n, 1<=v<=n */
void addEdge(Graph G, int u, int v){
	if(G == NULL){
 		printf("Graph Error: Cannot call addEdge() on an empty Graph\n");
 		exit(EXIT_FAILURE);
 	}

 	if(u > getOrder(G) || u < 1){
 		printf("Graph Error: Cannot call addEdge() with out of bounds value u\n");
 		exit(EXIT_FAILURE);
 	}

 	if(v > getOrder(G) || v < 1){
 		printf("Graph Error: Cannot call addEdge() with out of bounds value v\n");
 		exit(EXIT_FAILURE);
 	}

 	addArc(G, u, v);
 	
 	//G->size++;
}

// Actual depth first search
/* Pre: length(S)==getOrder(G) */
void DFS(Graph G, List S){
	/*if(length(S) == getOrder(G)){
		printf("Graph Error: Cannot call DFS() on different sized lists\n");
		exit(0);
	}*/

	if(length(S) != getOrder(G)){
		return;
	}

	int time;

	for(int x = 1; x <= getOrder(G); x++){
		G->c[x] = W;
		G->p[x] = NIL;
		G->d[x] = UNDEF;
		G->f[x] = UNDEF;
	}
	time = 0;
	moveFront(S);

	while(index(S) >= 0){
		int tmp = get(S);
		if(G->c[tmp] == W){
			Visit(G, S, tmp, &time);
		}
		moveNext(S);
	}

	for(int j = 1; j <= getOrder(G); j++){
		deleteBack(S);
	}

	G->size = G->size++;
}


void Visit(Graph G, List S, int x, int *time){
	G->d[x] = ++*time;		// discover x
	G->c[x] = Gr;

	List lG = G->adjacentVert[x];
	moveFront(lG);

	while(index(lG) >= 0){
		int y = get(lG);
		if(G->c[y] == W){
			G->p[y] = x;
			Visit(G, S, y, time);
		}
		moveNext(lG);
	}
	G->c[x] = B;
	G->f[x] = ++*time;
	prepend(S, x);
}



/* Other Functions */

// returns a reference to a new graph object representing the transpose of G
Graph transpose(Graph G){
	if(G == NULL){
		printf("Graph Error: calling transpose() on null Graph\n");
		exit(0);
	}
	Graph transposed = newGraph(getOrder(G));
	List lG;

	for(int i = 1; i <= getOrder(G); i++){
		lG = G->adjacentVert[i];
		moveFront(lG);
		while(index(lG) >= 0){
			int tmp = get(lG);
			addArc(transposed, tmp, i);
			moveNext(lG);
		}
	}
	return transposed;
}

// returns a reference to a new graph which is a copy of G.
Graph copyGraph(Graph G){
	if(G == NULL){
		printf("Graph Error: calling transpose() on null Graph\n");
		exit(0);
	}

	Graph newG = newGraph(getOrder(G));

	for(int i = 1; i <= getOrder(G); i++){
		List lG = G->adjacentVert[i];
		moveFront(lG);

		while(index(lG) >= 0){
			int tmp = get(lG);
			addArc(newG, i, tmp);
			moveNext(lG);
		}
	}

	return newG;
}

// prints out adjacency list representation
void printGraph(FILE* out , Graph G){
	if(out == NULL){
		printf("Graph Error: Cannot call printGraph() with no output location\n");
 		exit(EXIT_FAILURE);
	}

	if(G == NULL){
		printf("Graph Error: Cannot call printGraph() on an empty Graph\n");
 		exit(EXIT_FAILURE);
	}

	//printf("orig\n");
	for(int i = 1; i <= getOrder(G); i++){
		//printf("1\n");
		fprintf(out, "%d: ", i);
		//printf("2\n");
		printList(out, G->adjacentVert[i]);
		//printf("3\n");
		fprintf(out, "\n");
	}
}

