/*******************************************************************************
 * A graph isomorphism decision program based on iteractive relabeling algorithm.
 * Author: Marcos Daniel Baroni (marcosdaniel.baroni@gmail.com)
 * date: jan. 2012
 * This file can not be copied and/or distributed without the express
 * permission of the author.
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/times.h>

#include "pig.h"
#include "graph.h"

int main(int argc, char **argv){
        Graph *g1, *g2;
        FILE *f1, *f2;
        int *iso;    /* array, which will save the isomorphism found (if it exists). */

        if(argc < 3){
                printf("usage ./isom <graph 1> <graph 2>\n");
                return 1;
        }
	
        /* Reading input graphs */
        f1 = fopen(argv[1], "r");
        f2 = fopen(argv[2], "r");

        g1 = read_graph_adjlist(f1);
        g2 = read_graph_adjlist(f2);

        fclose(f1);
        fclose(f2);

        /* solving isomorphism */
        iso = AEPIG(g1, g2);

        printf("%s\n", iso ? "ISO" : "NOP");

        free_graph(g1);
        free_graph(g2);

        if(iso)
			free(iso);

        return 0;
}
