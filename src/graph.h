/*******************************************************************************
 * A graph isomorphism decision program based on iteractive relabeling algorithm.
 * Author: Marcos Daniel Baroni (marcosdaniel.baroni@gmail.com)
 * date: jan. 2012
 * This file can not be copied and/or distributed without the express
 * permission of the author.
*******************************************************************************/
#ifndef GRAPH_H_
#define GRAPH_H_ 1

#include <stdio.h>
#include "util.h"

void fdebug(char *str);

/******** Graph representation **********************************/
typedef struct Graph{
	int n, m;     /* vertex number, edge number */
	int **lists;  /* lists[i] store a vector with the... */
	int *nm;      /* ..."nm[i]" vertexs adjacents to vertex "i". */
	int regular;  /* if its regular */
}Graph;

/* Functions prototype */
Graph *read_graph_adjlist(FILE *f);
Graph *new_graph_from_mat(int **mat, int n); /* RETURNS A NEW GRAPH BUILT FROM A (INTEGER) ADJACENCY MATRIX */
Graph *new_graph_from_adjmat_file_opened(FILE *file);
Graph *graph_relabel(Graph *g, int *iso);
Graph *new_graph_from_adjmat_file(char *file); /* RETURNS A NEW GRAPH READ FROM A ADJACENCY MATRIX FILE (OCTAVE PATTERN) */
Graph *new_graph_from_adjlist_file(char *file); /* RETURNS A NEW GRAPH READ FROM A ADJACENCY LIST FILE (MY "HOMEMADE" PATTERN) */

void free_graph(Graph *g);
int graph_has_edge(Graph *g, int a, int b);
int graph_is_regular(Graph *g);
int graph_get_n(Graph *g);
int graph_get_m(Graph *g);
/****************************************************************/

int *graph_count2dist(Graph *g);
int *graph_count3dist(Graph *g);


#endif

