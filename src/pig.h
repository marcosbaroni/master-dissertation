/*******************************************************************************
 * A graph isomorphism decision program based on iteractive relabeling algorithm.
 * Author: Marcos Daniel Baroni (marcosdaniel.baroni@gmail.com)
 * date: jan. 2012
 * This file can not be copied and/or distributed without the express
 * permission of the author.
*******************************************************************************/
#ifndef ISOM_H_
#define ISOM_H_ 1

#include "graph.h"
#include "util.h"

int *AEPIG(Graph *g1, Graph *g2);
int *group_vertices(Graph *g, int *niter);
int same_degree_seq(Graph *g1, Graph *g2);
void vclasses_power_method(Graph *g);
int cmp_vclass_byclas(const void *vc1, const void *vc2);
int cmp_vgroup_n(const void *vc1, const void *vc2);

typedef struct vClass{
	int vertex;
	int clas;
}vClass;

typedef struct vGroup{
	int n;
	int *vs;
}vGroup;

typedef struct vGroups{
	int n;
	vGroup **groups;
}vGroups;

/* A Graph Isomorphism Problem Instance */
typedef struct PIG{
	int n;
	Graph *g1, *g2;
	vGroups *vgs1, *vgs2;
	vClass *vcs1, *vcs2;
	int *iso1, *iso2;
}PIG;

#endif

