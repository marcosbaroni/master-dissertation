/*******************************************************************************
 * A graph isomorphism decision program based on iteractive relabeling algorithm.
 * Author: Marcos Daniel Baroni (marcosdaniel.baroni@gmail.com)
 * date: jan. 2012
 * This file can not be copied and/or distributed without the express
 * permission of the author.
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "util.h"
#include "graph.h"

int cmp_int_tuple_asc( const void *x, const void *y){
	if(((int*)x)[0] == ((int*)y)[0])
		return (((int*)x)[1] - ((int*)y)[1]);
	else return (((int*)x)[0] - ((int*)y)[0]);
}

int cmp_int_tuple_desc( const void *x, const void *y){
	if(((int*)x)[1] == ((int*)y)[1])
		return (((int*)x)[0] - ((int*)y)[0]);
	else return (((int*)x)[1] - ((int*)y)[1]);
}

/****************************************************************************
*	RETURNS A NEW GRAPH READ FROM A ADJACENCY LIST FILE 
*
* ////////////////
* // <nvertex>  //
* // <nedges>   //
* // <edge1>    //
* // <edge2>    //
* //  ...       //
* // <edgem>    //
* ////////////////
* // Ex. for K4 //
* // 4          //
* // 6          //
* // 1 2        //
* // 1 3        //
* // 1 4        //
* // 2 3        //
* // 2 4        //
* // 3 4        //
* ////////////////
*
****************************************************************************/
Graph *read_graph_adjlist(FILE *f){
	int err, i, n, m, a, b, k;
	Graph *g;
	int *v;

	g = NULL;
	err = fscanf(f, "%d %d", &n, &m);
	if( err == EOF || err < 2 ){
		fprintf(stderr, "error reading input file\n");
		return NULL;
	}

	g = (Graph*)malloc(sizeof(Graph));
	g->n = n;
	g->regular = 1;
	g->nm = (int*)malloc(n*sizeof(int));
	for( i = 0 ; i < n ; i++ )
		g->nm[i] = 0;
	g->lists = (int**)malloc(n*sizeof(int*));
	v = (int*)malloc(2*m*sizeof(int));

	k = 0;
	for( i = 0 ; i < m ; i++ ){
		err = fscanf(f, "%d %d", &a, &b);
		a--; b--;
		if( err < 2 ){
			fprintf(stderr, "error reading %d=th edge\n", i+1); break;
		}else if( a < 0 || b < 0 || a > n-1 || b > n-1 ){
			fprintf(stderr, "error reading %d-th edge: (%d, %d) does not exists\n", i+1, a+1, b+1);
		}else{
			v[2*k] = a;
			v[2*k+1] = b;
			g->nm[a]++;
			g->nm[b]++;
			k++;
		}
	}

	for( i = 0 ; i < n ; i++ ){
		g->lists[i] = (int*)malloc(g->nm[i]*sizeof(int));
		g->nm[i] = 0;
	}

	g->m = 0;
	for( i = 0 ; i < k ; i++ ){
		a = v[2*i]; b = v[2*i+1];
		g->lists[a][g->nm[a]++] = b;
		g->lists[b][g->nm[b]++] = a;
		g->m++;
	}

	for( i = 1 ; i < n ; i++ )
		if( g->nm[i-1] != g->nm[i] )
			g->regular = 0;

	for( i = 0 ; i < n ; i++ )
		int_quicksort(g->lists[i], g->nm[i]);

	free(v);

	return g;
}

int graph_is_regular(Graph *g){
	return g->regular;
}

int graph_has_edge(Graph *g, int a, int b){
	int m, i;
	int *l;
	m = g->nm[a];
	l = g->lists[a];
	for( i = 0 ; i < m ; i++ )
		if(l[i] == b)
			return 1;
	return 0;
}

/******************************************************************
*   RETURNS A NEW GRAPH BUILT FROM AN (INTEGER) ADJACENCY MATRIX
******************************************************************/
Graph *new_graph_from_mat(int **mat, int n){
	int i, j, k, m, count, last_m;
	Graph *g;

	/*   ALLOCING GRAPH   */
	g = (Graph*)malloc(sizeof(Graph));
	g->nm = (int*)malloc(n*sizeof(int));
	g->lists = (int**)malloc(n*sizeof(int*));

	m = 0; /* edge quantity */

	/*   FILLING GRAPH   */
	g->n = n;
	last_m = 0;
	g->regular = 1;
	for( i = 0 ; i < n ; i++ ){ /* FOR EACH VERTEX */
		count = 0;
		/*   COUNTING ADJACENT EDGES   */
		for( j = 0 ; j < n ; j++ )
			if(mat[i][j])
				count++;

		/*   CHECKING IF ITS REGULAR    */
		if(last_m && count != last_m)
			g->regular = 0;
		last_m = count;

		/*   ALLOCING ADJACENCY LIST   */
		g->lists[i] = (int*)malloc(count*sizeof(int));

		/*   FILLING ADJACENCY LIST   */
		k = 0;
		for( j = 0 ; j < n ; j++ )
			if(mat[i][j])
				g->lists[i][k++] = j;
		g->nm[i] = count;
		m += count;
	}
	m = m/2;
	g->m = m;

	return g;
}

/****************************************************************************
*	RETURNS A NEW GRAPH READ FROM A ADJACENCY LIST FILE (MY "HOMEMADE" PATTERN)
*
* ////////////////
* // <nvertex>	//
* // <nedges>	//
* // <edge1>	//
* // <edge2>	//
* //  ...	//
* // <edgem> 	//
* ////////////////
* // Ex. for K4	//
* // 4		//
* // 6		//
* // 1 2	//
* // 1 3	//
* // 1 4	//
* // 2 3	//
* // 2 4	//
* // 3 4	//
* ////////////////
*
****************************************************************************/
Graph *new_graph_from_adjlist_file(char *file){
	FILE *f;
	int i, j, n, m, a, b;
	int **mat;
	Graph *g;

	/* OPENING FILE */
	f = fopen(file, "r");

	fscanf(f, "%d", &n);
	fscanf(f, "%d", &m);

	/*   ALLOCING MATRIX    */
	mat = (int**)malloc(n*sizeof(int*));
	for( i = 0 ; i < n ; i++ )
		mat[i] = (int*)malloc(n*sizeof(int));
	
	/*   INITIALIZING MATRIX   */
	for( i = 0 ; i < n ; i++ )
		for( j = 0 ; j < n ; j++ )
			mat[i][j] = 0;
	
	/*   READING MATRIX    */
	for( i = 0 ; i < m ; i++ ){
		fscanf(f, "%d %d", &a, &b);
		mat[a-1][b-1] = 1;
		mat[b-1][a-1] = 1;
	}

	fclose(f); /* closing file */

	/*   BUILDING NEW GRAPH FROM MATRIX   */
	g = new_graph_from_mat(mat, n);

	/*   FREEING MATRIX   */
	for( i = 0 ; i < n ; i++ )
		free(mat[i]);
	free(mat);

	return g;
}

Graph *graph_relabel(Graph *g, int *iso){
	int i, j, n, m;
	int *adj, **lists, *nm;

	n = g->n;
	lists = (int**)malloc(n*sizeof(int*));
	nm = (int*)malloc(n*sizeof(int));

	/* Relabeling vertices on adjacency lists */
	for( i = 0 ; i < n ; i++ ){
		m = g->nm[i];
		adj = g->lists[i];
		for( j = 0 ; j < m ; j++ )
			adj[j] = iso[adj[j]];
		lists[iso[i]] = adj;
		nm[iso[i]] = m;
	}

	free(g->lists);
	free(g->nm);

	g->lists = lists;
	g->nm = nm;

	return g;
}

int graph_get_n(Graph *g){
	return g->n;
}

int graph_get_m(Graph *g){
	return g->m;
}

Graph *graph_copy(Graph *g){
	int i, j, m, n;
	Graph *ng;

	ng = (Graph*)malloc(sizeof(Graph));
	n = g->n;
	ng->n = n;
	ng->m = g->m;
	ng->nm = (int*)malloc(n*sizeof(int));
	ng->lists = (int**)malloc(n*sizeof(int*));

	for( i = 0 ; i < n ; i++ ){
		m = ng->nm[i] = g->nm[i];
		ng->lists[i] = (int*)malloc(m*sizeof(int));
		for( j = 0 ; j < m ; j++ )
			ng->lists[i][j] = g->lists[i][j];
	}
	ng->regular = g->regular;
	return ng;
}

void fprint_graph_adjlist(FILE *f, Graph *g){
	int i, j, n, m;
	int *adj;
	n = g->n;
	fprintf(f, "%d %d\n", g->n, g->m);
	for( i = 0 ; i < n ; i++ ){
		fprintf(f, "%d: [", i+1);
		m = g->nm[i];
		adj = g->lists[i];
		for( j = 0 ; j < m-1 ; j++ )
			fprintf(f, "%d,", adj[j]+1);
		if(m) fprintf(f, "%d", adj[m-1]+1);
		fprintf(f, "]\n");
	}
	fprintf(f, "\n");
	return;
}

void fprint_graph(FILE *f, Graph *g){
	int i, j, m;
	fprintf(f, "%d %d\n", g->n, g->m);
	for( i = 0 ; i < g->n ; i++ ){
		m = g->nm[i];
		for( j = 0 ; j < m ; j++ )
			if( g->lists[i][j] > i )
				fprintf(f, "%d %d\n", i+1, g->lists[i][j]+1);
	}
	return;
}

void fprint_graph_adjmat(FILE *f, Graph *g){
	int n, m, i, j;
	int *v, *adj;

	n = g->n;
	v = (int*)malloc(n*sizeof(int));

	for( i = 0 ; i < n ; i++ )
		v[i] = 0;

	for( i = 0 ; i < n ; i++ ){
		adj = g->lists[i];
		m = g->nm[i];

		for( j = 0 ; j < m ; j++ )
			v[adj[j]] = 1;

		for( j = 0 ; j < n-1 ; j++ )
			fprintf(f, "%d ", v[j]);

		if(n) fprintf(f, "%d\n", v[n-1]);
		for( j = 0 ; j < m ; j++ )
			v[adj[j]] = 0;
	}

	free(v);

	return;
}


void free_graph(Graph *g){
	int i;
	if(!g) return;
	for( i = 0 ; i < g->n ; i++ ){
		free(g->lists[i]);
	}
	free(g->lists);
	free(g->nm);
	free(g);
	return;
}

/*
	This function counts how many "two-edges distant" neighbors it has.
	(It counts itself to.)
*/
int *graph_count2dist(Graph *g){
	int a, b, i, j, k, n, m, m2;
	int *v, *v1, *v2, *adj, *adj2;

	n = g->n;
	v = (int*)malloc(n*sizeof(int));
	v1 = (int*)malloc(n*sizeof(int));
	v2 = (int*)malloc(n*sizeof(int));

	for( i = 0 ; i < n ; i++ ){
		m = g->nm[i];
		adj = g->lists[i];
		v[i] = 0;
		for( j = 0 ; j < n ; j++ )
			v1[j] = v2[j] = 0;
		for( j = 0 ; j < m ; j++ )
			v1[adj[j]] = 1;
		for( j = 0 ; j < m ; j++ ){
			a = adj[j];
			m2 = g->nm[a];
			adj2 = g->lists[a];
			for( k = 0 ; k < m2 ; k++ ){
				b = adj2[k];
				if( b != i && !v1[b] && !v2[b] ){
					v2[b] = 1;
					v[i]++;
				}
			}
		}
	}

	free(v1);
	free(v2);

	return v;
}

int *graph_count3dist(Graph *g){
	int a, b, c, i, j, k, l, n, m, m2, m3;
	int *v, *v1, *v2, *v3, *adj, *adj2, *adj3;

	n = g->n;
	v = (int*)malloc(n*sizeof(int));
	v1 = (int*)malloc(n*sizeof(int));
	v2 = (int*)malloc(n*sizeof(int));
	v3 = (int*)malloc(n*sizeof(int));

	for( i = 0 ; i < n ; i++ ){
		m = g->nm[i];
		adj = g->lists[i];
		v[i] = 0;
		for( j = 0 ; j < n ; j++ )
			v1[j] = v2[j] = v3[j] = 0;
		for( j = 0 ; j < m ; j++ )
			v1[adj[j]] = 1;
		for( j = 0 ; j < m ; j++ ){
			a = adj[j];
			m2 = g->nm[a];
			adj2 = g->lists[a];
			for( k = 0 ; k < m2 ; k++ ){
				b = adj2[k];
				if( b != i && !v1[b] )
					v2[b] = 1;
			}
		}
		for( j = 0 ; j < m ; j++ ){
			a = adj[j];
			m2 = g->nm[a];
			adj2 = g->lists[a];
			for( k = 0 ; k < m2 ; k++ ){
				b = adj2[k];
				m3 = g->nm[b];
				adj3 = g->lists[b];
				for( l = 0 ; l < m3 ; l++ ){
					c = adj3[l];
					if( !v1[c] && !v2[c] && c != i && !v3[c] ){
						v3[c] = 1;
						v[i]++;
					}
				}
			}
		}
	}

	free(v1);
	free(v2);
	free(v3);

	return v;
}


