//Sebastian Medina                   CruzID: Seamedin                        Course: CSE 101
//December 5, 2019                   FIlename: GraphTest.c
//Description: Test the graph ADT

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(){
	Graph A = newGraph(8);
	
	int verts = getOrder(A);
	printf("# of vertices in graph A: %d\n", verts);

	addEdge(A, 1, 2);
	addEdge(A, 2, 5);
	addEdge(A, 2, 3);
	addEdge(A, 2, 6);
	addEdge(A, 5, 6);
	addEdge(A, 5, 1);
	addEdge(A, 3, 4);
	addEdge(A, 3, 7);
	addEdge(A, 4, 3);
	addEdge(A, 4, 8);
	addEdge(A, 6, 7);
	addEdge(A, 7, 6);
	addEdge(A, 7, 8);
	addEdge(A, 8, 8);
	printf("# of edges in graph A: %d\n", getSize(A));

	printf("\nAdjacency list of A: \n");
	printGraph(stdout, A);

	// Run DFS
	List m = newList();
	Graph aT;
	DFS(A, m);

	aT = transpose(A);

	printf("\nAdjacency list of A^T: \n");
	printGraph(stdout, aT);

	List m2 = newList();
	DFS(aT, m2);

	return 0;
}
