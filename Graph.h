//Sebastian Medina                  CruzID: Seamedin           Course: CSE 101
//December 5, 2019                  FIlename: Graph.h 
//Description: Header for file for graph data type

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "List.h"
#define NIL 0
#define INF -1
#define UNDEF -100

//Graph reference type
typedef struct GraphObj* Graph;


/* Constructors-Destructors */

// creates new graph
Graph newGraph(int n);

// free's graph from memory
void freeGraph(Graph* pG);

/* Access functions */

// returns the # of vertices
int getOrder(Graph G);

// returns # of edges
int getSize(Graph G);

// returns parent of vertex
int getParent(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */

// returns discover time of vertex
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */

// returns finish time of vertex
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */

/* Manipulation procedures */

// inserts a new directed edge from u to v
// i.e. v is added to the adjacency List of u
void addArc(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */


// inserts a new edge joining u to v, i.e. u is added to the adjacency List
void addEdge(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */

// Actual depth first search
void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */

/* Other Functions */

// returns a reference to a new graph object representing the transpose of G
Graph transpose(Graph G);

// returns a reference to a new graph which is a copy of G.
Graph copyGraph(Graph G);

// prints out adjacency list representation
void printGraph(FILE* out , Graph G);


#endif
