#ifndef _GRAFO_MATRIZ_H_
#define _GRAFO_MATRIZ_H_

#include <stdlib.h>
#include <stdio.h>
#include "int_arr.h"

#define EMPTY -1

typedef struct {
    int **matrix;
    int n, digraph;
} GRAPH_M;

GRAPH_M *create_graph_m(int, int);
void insert_new_edge_m(GRAPH_M *, int, int, int);
int exists_edge_m(GRAPH_M *, int, int);
void remove_edge_m(GRAPH_M *, int, int);
void print_graph_m(GRAPH_M *);
INT_ARR *adj_vertexes_m(GRAPH_M *, int);
void print_least_weighted_edge_m(GRAPH_M *);
void print_transpose_graph_m(GRAPH_M *);
void free_graph_m(GRAPH_M *);
INT_ARR *source_vertex_graph_m(GRAPH_M *);

#endif
