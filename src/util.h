/*******************************************************************************
 * A graph isomorphism decision program based on iteractive relabeling algorithm.
 * Author: Marcos Daniel Baroni (marcosdaniel.baroni@gmail.com)
 * date: jan. 2012
 * This file can not be copied and/or distributed without the express
 * permission of the author.
*******************************************************************************/
#ifndef ISO_UTIL_H_
#define ISO_UTIL_H_ 1

#include <time.h>
#include <sys/time.h>
#include <stdio.h>

#define CHAR_BUFFER_SIZE 50000
#define MICROSECS_PER_SECOND 1000000
#define max(a,b) (a > b ? a : b)
#define min(a,b) (a < b ? a : b)

int *int_quicksort( int *v, int n);

int cmpint(const void *a, const void *b);
int		eq_groups(int *v1, int *v2, int n);
int		count_groups(int *v, int n);
typedef struct{
	int n;       /* number of elements */
	int k;       /* number of entries */
	int **as;    /* table */
	int *ns;     /* size of each entry */
	int *nmaxs;  /* max size of each entry */
}IntHashTable;

IntHashTable *new_inthashtable(int k);
int inthashtable_has(IntHashTable *h, int a);
IntHashTable *inthashtable_insert(IntHashTable *h, int a);
IntHashTable *inthashtable_reset(IntHashTable *h);
void free_inthashtable(IntHashTable *h);

int table[1000];

#endif

