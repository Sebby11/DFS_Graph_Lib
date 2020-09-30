//Sebastian Medina                       CruzID: Seamedin                Course: CSE 101
//December 5, 2019                       FIlename: FindComponents.c
//Description: Finds the strongly connected components of a graph.

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

int main(int argc, char *argv[]) {
	FILE *in;
	FILE *out;

	if(argc != 3){
		printf("Usage: FindPath <input file> <output file>\n");
 		exit(EXIT_FAILURE);
	}

	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");

	if(in == NULL){
		fprintf(out,"Input file could not be read\n");
 		exit(EXIT_FAILURE);
	}
	else if(out == NULL){
		fprintf(out,"Output file could not set to write to\n");
 		exit(EXIT_FAILURE);
	}

	fprintf(out, "Adjacency list representation of G:\n");
	int numVerts;
	int v1, v2;
	List temp = newList();
	Graph A, aT;

	// get n
	fscanf(in, "%d", &numVerts);
	A = newGraph(numVerts);

	// fill list
	for(int i = 1; i <= getOrder(A); i++){
		append(temp, i);
	}

	// get edges in garph A
	while(fscanf(in, "%d %d", &v1, &v2) == 2){
		if(v1 == 0 && v2 == 0){
			break;
		}
		addEdge(A, v1, v2);
	}

	printGraph(out, A);
	fprintf(out, "\n" );

	// RUN DFS
	DFS(A, temp);

	// transpose
	aT = transpose(A);
	DFS(aT, temp);

	int numStrongs = 0;
	for(int j = 1; j<= getOrder(A); j++){
		if(getParent(aT, j) == NIL)
			numStrongs++;
	}

	//fprintf(out, "Adjacency list representation of G:\n");
	fprintf(out, "G contains %d strongly connected components:\n", numStrongs);

	//get the strongly connected components
	List tmp = newList();
	moveBack(temp);

   	int componCount = 1;
	while(index(temp) >= 0){
		prepend(tmp, get(temp));
		if(getParent(aT, get(temp)) == NIL){
			fprintf(out, "Component %d: ", componCount);
			printList(out, tmp);
			fprintf(out, "\n" );
			clear(tmp);
			componCount++;
		}
		movePrev(temp);
	}

	freeGraph(&A);
	freeGraph(&aT);
	freeList(&tmp);
	freeList(&temp);

	fclose(in);
	fclose(out);
}












