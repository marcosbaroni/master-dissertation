/*******************************************************************************
 * A graph isomorphism decision program based on iteractive relabeling algorithm.
 * Author: Marcos Daniel Baroni (marcosdaniel.baroni@gmail.com)
 * date: jan. 2012
 * This file can not be copied and/or distributed without the express
 * permission of the author.
*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "pig.h"
#include "graph.h"
#include "util.h"

void print_vclasses(vClass *vcs, int n){
	int i;
	for( i = 0 ; i < n ; i++ )
		printf("[%d, %d]\n", vcs[i].vertex+1, vcs[i].clas);
	printf("\n");
}

int cmp_vclass_byclas(const void *vc1, const void *vc2){
	return ((vClass*)vc1)->clas - ((vClass*)vc2)->clas;
}

int cmp_vclass_byvertex(const void *vc1, const void *vc2){
	return ((vClass*)vc1)->vertex - ((vClass*)vc2)->vertex;
}

int cmp_vgroup_n(const void *vc1, const void *vc2){
	return ((vGroups*)vc1)->n - ((vGroups*)vc2)->n;
}

vClass *_sub_vclasses_power_method(Graph *g, vClass *vcs){
	int n, m, i, j, last_clas;
	int *adj, *vaux;

	n = g->n;
	vaux = (int*)malloc(n*sizeof(int));

	for( i = 0 ; i < n; i++ ){
		adj = g->lists[i];
		m = g->nm[i];
		vaux[i] = 0;
		for( j = 0 ; j < m ; j++ )
			vaux[i] += vcs[adj[j]].clas;
	}

	for( i = 0 ; i < n ; i++ )
		vcs[i].clas = vaux[i];

	for( i = 0 ; i < n; i++ ){
		adj = g->lists[i];
		m = g->nm[i];
		vaux[i] = 0;
		for( j = 0 ; j < m ; j++ )
			vaux[i] += vcs[adj[j]].clas;
	}

	for( i = 0 ; i < n ; i++ )
		vcs[i].clas = vaux[i];

	qsort(vcs, n, sizeof(vClass), cmp_vclass_byclas);

	j = 0;
	last_clas = vcs[0].clas;
	vcs[0].clas = j;
	for( i = 1 ; i < n ; i++ ){
		if( vcs[i].clas != last_clas )
			j++;
		last_clas = vcs[i].clas;
		vcs[i].clas = j;
	}

	qsort(vcs, n, sizeof(vClass), cmp_vclass_byvertex);

	return vcs;
}

void vclasses_power_method(Graph *g){
	vClass *vcs;
	int n, i;
	
	n = g->n;
	vcs = (vClass*)malloc(n*sizeof(vClass));
	for( i = 0 ; i < n ; i++ ){
		vcs[i].vertex = i;
		vcs[i].clas = g->nm[i];
	}

	vcs = _sub_vclasses_power_method(g, vcs);
	vcs = _sub_vclasses_power_method(g, vcs);
	vcs = _sub_vclasses_power_method(g, vcs);
	vcs = _sub_vclasses_power_method(g, vcs);
	vcs = _sub_vclasses_power_method(g, vcs);
	vcs = _sub_vclasses_power_method(g, vcs);

	free(vcs);

	return;
}

int *build_filter(Graph *g, int *modfs){
	int *v;
	v = NULL;

	return v;
}

/*
	Checks if the association (ve1, ve2) is valid considering the
current isomorphism attempt (if not the algorithm may backtrack).
	ve1 E V1
	ve2 E V2
*/
int valid_association(PIG *p, int ve1, int ve2){
	int m1, m2, i, valid;
	int *adj1, *adj2;

	/* Respective degrees */
	m1 = p->g1->nm[ve1];
	m2 = p->g2->nm[ve2];

	/* Respective adjacencies */
	adj1 = p->g1->lists[ve1];
	adj2 = p->g2->lists[ve2];

	valid = 1;
	/* Checking for G1 |-> G2 association consistency */
	for( i = 0 ; i < m1 && valid ; i++ )
		/* If has a vertex on G2 assigned to it */
		if( p->iso1[adj1[i]] > 0 )
			/* If the edge doesnt exists */
			if( !graph_has_edge(p->g2, ve2, p->iso1[adj1[i]]) )
				valid = 0;

	/* Checking for G2 |-> G1 association consistency */
	for( i = 0 ; i < m2 && valid ; i++ )
		/* If has a vertex on G1 assigned to it */
		if( p->iso2[adj2[i]] > 0 )
			/* If the edge doesnt exists */
			if( !graph_has_edge(p->g1, ve1, p->iso2[adj2[i]]) )
				valid = 0;

	return valid;
}

/*
	p: the PIG problem instance being solved
	cg: current association group
	in: vertex already fixed for current association group
*/
int *sub_isomorphism_check(PIG *p, int cg, int in){
	int i, n, gn, ve1, ve2;
	int valid_a, *iso_found;

	n = p->g1->n;
	gn = p->vgs1->groups[cg]->n;
	iso_found = NULL;

	/* Vertex in g1 */
	ve1 = p->vgs1->groups[cg]->vs[in];
	/* Looking for an available vertex on g2 to be matched */
	for( i = 0 ; i < gn && !iso_found ; i++ ){
		ve2 = p->vgs2->groups[cg]->vs[i];
		/* If not mapped yet */
		if( p->iso2[ve2] < 0 ){
			/* Check if (ve1 -> ve2) is a valid association */

			valid_a = valid_association(p, ve1, ve2);
			if( valid_a ){
				/* Recording association try */
				p->iso1[ve1] = ve2;
				p->iso2[ve2] = ve1;
 				/* All vertices from current association group matched? */
				if( in+1 == p->vgs1->groups[cg]->n ){
					/* No association groups left to be matched? */
					if( cg+1 == p->vgs1->n ){
						/* Copying isomorhpism found */
						iso_found = (int*)malloc(n*sizeof(int));
						memcpy(iso_found, p->iso1, n*sizeof(int));
					}else{
						/* Work on next association group */
						iso_found = sub_isomorphism_check(p, cg+1, 0);
					}
				}else{
 					/* Seek association for the next vertex in group */
					iso_found = sub_isomorphism_check(p, cg, in+1);
				}
 				/* Erasing association try */
				p->iso1[ve1] = p->iso2[ve2] = -1;
			}
		}
	}
	return iso_found;
}


int *isomorphism_check(Graph *g1, Graph *g2, vGroups *vgs1, vGroups *vgs2, vClass *vcs1, vClass *vcs2){
	int *iso1, *iso2, *iso_found;
	int i, n;
	PIG p;

	n = g1->n;
	iso1 = (int*)malloc(n*sizeof(int));
	iso2 = (int*)malloc(n*sizeof(int));

	/* Initializing isomorphism (all empty) */
	for( i = 0 ; i < n ; i++ ) iso1[i] = iso2[i] = -1; /* no matching yet */

	/* Sorting vertex groups */
	/* qsort(vgs1, ngs1->n, sizeof(vGroups), cmp_vgroup_n); */
	/* qsort(vgs2, ngs2->n, sizeof(vGroups), cmp_vgroup_n); */


	/* Setting up the problem instance */
	p.g1 = g1; p.g2 = g2;			/* Graphs */
	p.iso1 = iso1; p.iso2 = iso2;	/* Matchings (value iso1[i] is how i (from g1) is called on g2, i.e., iso1(x) : V(g1) |-> V(g2) ) */
	p.vgs1 = vgs1; p.vgs2 = vgs2;	/* Vertices grouping */
	p.vcs1 = vcs1; p.vcs2 = vcs2;	/* Class (centrality) of each vertex */

	/* Solving problem instance */
	iso_found = sub_isomorphism_check(&p, 0, 0);

	free(iso1);
	free(iso2);

	return iso_found;
}

void free_vgroups(vGroups *vgs){
	int i, n;
	n = vgs->n;
	for( i = 0 ; i < n ; i++ ){
		free(vgs->groups[i]->vs);
		free(vgs->groups[i]);
	}
	free(vgs->groups);
	free(vgs);
	return;
}

/* Builds an array with information about each vertex class */
vClass *buildClasses(int *v, int n){
	int i;
	vClass *vc = (vClass*)malloc(n*sizeof(vClass));
	for( i = 0 ; i < n ; i++ ){
		vc[i].vertex = i;
		vc[i].clas = v[i];
	}
	return vc;
}

/*   Builds centrality groups (used on matching attempts)   */
vGroups *buildGroups(vClass *vc, int n){
	int i, j, current_group_size, n_groups, current_class;
	vGroup **gs = (vGroup**)malloc(n*sizeof(vGroup*));
	vGroup *new_group;
	vGroups *res;

	n_groups = 0;
	current_group_size = 1;
	current_class = vc[0].clas;
	for( i = 1 ; i < n ; i++ ){
		if( vc[i].clas == current_class ){
			current_group_size++;
		}else{
			new_group = (vGroup*)malloc(sizeof(vGroup));
			new_group->n = current_group_size;
			new_group->vs = (int*)malloc(current_group_size*sizeof(int));
			for( j = 0 ; j < current_group_size ; j++ )
				new_group->vs[current_group_size-j-1] = vc[i-j-1].vertex;
			gs[n_groups] = new_group;
			n_groups++;
			current_group_size = 1;
			current_class = vc[i].clas;
		}
	}

	/* building last group */
	if(current_group_size > 0){
		new_group = (vGroup*)malloc(sizeof(vGroup));
		new_group->n = current_group_size;
		new_group->vs = (int*)malloc(current_group_size*sizeof(int));
		for( j = 0 ; j < current_group_size ; j++ )
			new_group->vs[j] = vc[n-1-j].vertex;
		gs[n_groups] = new_group;
		n_groups++;
		current_group_size = 0;
	}

	/* coping the real group size */
	res = (vGroups*)malloc(sizeof(vGroups));
	res->n = n_groups;
	res->groups = (vGroup**)malloc(n_groups*sizeof(vGroup*));
	for( i = 0 ; i < n_groups ; i++ )
		res->groups[i]  = gs[i];

	free(gs);
	return res;
}

void fprint_vgroups(FILE *out, vGroups *gs){
	int i, j, n, m;
	int *v;
	n = gs->n;
	for( i = 0 ; i < n ; i++ ){
		m = gs->groups[i]->n;
		v = gs->groups[i]->vs;
		fprintf(out, "%d:\t[", i+1);
		if(m) fprintf(out, "%d", v[0]+1);
		for( j = 1 ; j < m ; j++ )
			fprintf(out, ",%d", v[j]+1);
		fprintf(out, "]\n");
	}
	fprintf(out, "\n");
	return;
}

/* Checks if graph has the same vertices degree sequence */
int same_degree_seq(Graph *g1, Graph *g2){
	int i, n, same;
	int *v1, *v2;

	/* Same number of vertex ? */
	if( g1->n != g2->n ) return 0;

	/* Same number of edges ? */
	if( g1->m != g2->m ) return 0;
	
	n = g1->n;
	v1 = (int*)malloc(n*sizeof(int));
	v2 = (int*)malloc(n*sizeof(int));

	/* Copying degree vectors */
	memcpy(v1, g1->nm, n*sizeof(int));
	memcpy(v2, g2->nm, n*sizeof(int));

	/* Sorting degree vectors */
	qsort(v1, n, sizeof(int), cmpint);
	qsort(v2, n, sizeof(int), cmpint);

	same = 1;
	/* Checking degree vectors equivalence */
	for( i = 0 ; i < n ; i++ ){
		if( v1[i] != v2[i] ){
			same = 0;
			break;
		}
	}

	free(v1);
	free(v2);
	return same;
}

int *get_invariant(Graph *g){
	int *v, n;
	n = graph_get_n(g);

	/* graph is regular? */
	if( graph_is_regular(g) ){
		/* count dist2 neighbors */
		v = graph_count2dist(g);
		if( count_groups(v, n) == 1){
			/* count dist3 neighbors */
			free(v);
			v = graph_count3dist(g);
		}
	}else{
		/* use degree */
		v = (int*)malloc(n*sizeof(int));
		memcpy(v, g->nm, n*sizeof(int));
	}
	return v;
}

int *invprop_iteration(Graph *g, int *v, IntHashTable *h){
	int i, j, m, n;
	int *l, *newv;
	n = g->n;

	newv = (int*)malloc(n*sizeof(int));
	for( i = 0 ; i < n ; i++ ){
		m = g->nm[i];
		l = g->lists[i];
		newv[i] = v[i];
		for( j = 0 ; j < m ; j++ )
			newv[i] ^= table[v[l[j]]%1000];
		if(!inthashtable_has(h, newv[i]))
			inthashtable_insert(h, newv[i]);
	}
	return newv;
}

int *invprop(Graph *g, int *v, int *niter){
	IntHashTable *h;
	int n, new, old, k;
	int *vaux, *newv;
	k = 0;

	h = new_inthashtable(g->n);
	n = g->n;

	old = 1;
	newv = invprop_iteration(g, v, h);
	new = h->n;
	if( niter )
		*niter = 1;
	k++;

	while( new > old && new < n ){
		old = new;
		inthashtable_reset(h);
		vaux = invprop_iteration(g, newv, h);
		free(newv);
		newv = vaux;
		new = h->n;
		if( niter )
			*niter += 1;
		k++;
	}

	free_inthashtable(h);
	return newv;
}

int *group_vertices(Graph *g, int *niter){
	int *v1, *v2;
	v1 = get_invariant(g);
	v2 = invprop(g, v1, niter);
	free(v1);
	return v2;
}

int *AEPIG(Graph *g1, Graph *g2){
	int n1, n2, niter;
	int *v1, *v2, *iso1;
	vGroups *vgs1, *vgs2;
	vClass *vcs1, *vcs2;

	iso1 = NULL;

	/* Same degree sequence? */
	if( !same_degree_seq(g1, g2) ){
		/*fprintf(stderr, "Different degree sequences, not isomorphics.\n");*/
		return NULL;
	}

	n1 = g1->n;
	n2 = g2->n;

	niter = 0;

	/* Computing filter */
	v1 = group_vertices(g1, &niter);
	v2 = group_vertices(g2, &niter);

	if(!eq_groups(v1, v2, g1->n)){
		free(v1);
		free(v2);
		/*fprintf(stderr, "Different eigen-centralities, not isomorphics.\n");*/
		return NULL;
	}

	/* Building vertex classification */
	vcs1 = buildClasses(v1, n1);
	vcs2 = buildClasses(v2, n2);

	/* Sorting classification by centrality */
	qsort(vcs1, n1, sizeof(vClass), cmp_vclass_byclas);
	qsort(vcs2, n2, sizeof(vClass), cmp_vclass_byclas);

	/* Printing classification by centrality */
	/*print_vclasses(vcs1, n1);*/
	/*print_vclasses(vcs2, n2);*/

	/* Building association groups */
	vgs1 = buildGroups(vcs1, n1);
	vgs2 = buildGroups(vcs2, n2);
	//fprintf(stdout, "(%d groups, %d iters)\n", vgs1->n, niter); /* for debugging */

	/* Printing vertex groups */
	/*fprint_vgroups(stdout, vgs1); */
	/*fprint_vgroups(stdout, vgs2); */

	/* Sorting classification by label */
	qsort(vcs1, n1, sizeof(vClass), cmp_vclass_byvertex);
	qsort(vcs2, n2, sizeof(vClass), cmp_vclass_byvertex);

	/* *** Computing isomorhpism *** */
	if(vgs1->n != n1)     /* if exists a vertex group with more than one vertex */
		iso1 = isomorphism_check(g1, g2, vgs1, vgs2, vcs1, vcs2);

	/* Freeing eigen vetors */
	free(v1);
	free(v2);

	/* Freeing associoation groups */
	free_vgroups(vgs1);
	free_vgroups(vgs2);

	/* Freeing vertex classification */
	free(vcs1);
	free(vcs2);

	if(!iso1){
		fprintf(stderr, "Isomorphism not found, not isomorphics.\n");
		return NULL;
	}

	/* Returning (f : v1 |-> v2) if any, NULL otherwise */
	return iso1;
}

