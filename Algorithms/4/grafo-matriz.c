#include "grafo-matriz.h"

GRAPH_M *create_graph_m(int size, int digraph) {
    int iterations = 0;
    GRAPH_M *graph_m = (GRAPH_M *) malloc(sizeof(GRAPH_M));
    int i, j;

    // creates an matrix (size X size)
    graph_m->n = size;
    graph_m->digraph = digraph;
    graph_m->matrix = (int **) malloc(sizeof(int *) * size);
    
    for (i = 0; i < size; i++)
	graph_m->matrix[i] = (int *) malloc(sizeof(int) * size);

    // reseting matrix
    for (i = 0; i < size; i++)
	for (j = 0; j < size; j++)
	    graph_m->matrix[i][j] = EMPTY;

    iterations++;
    return graph_m;	
}

void insert_new_edge_m(GRAPH_M *graph_m, int vertex_a, int vertex_b, int weight) {
    graph_m->matrix[vertex_a][vertex_b] = weight;
    
    if (!graph_m->digraph)
	graph_m->matrix[vertex_b][vertex_a] = weight;
}

int exists_edge_m(GRAPH_M *graph_m, int vertex_a, int vertex_b) {
    return (graph_m->matrix[vertex_a][vertex_b] != EMPTY);
}

void remove_edge_m(GRAPH_M *graph_m, int vertex_a, int vertex_b) {
    graph_m->matrix[vertex_a][vertex_b] = EMPTY;
    
    if (!graph_m->digraph)
	graph_m->matrix[vertex_b][vertex_a] = EMPTY;
}

void print_graph_m(GRAPH_M *graph_m) {
    int i, j;

    for (i = 0; i < graph_m->n; i++) {
	for (j = 0; j < graph_m->n; j++) {
	    if (graph_m->matrix[i][j] != EMPTY)
		printf("%d ", graph_m->matrix[i][j]);
	    else
		printf(". ");
	}

	printf("\n");
    }
}

INT_ARR *adj_vertexes_m(GRAPH_M *graph_m, int vertex) {
	INT_ARR *adj = malloc(sizeof(INT_ARR));
    int i, j, aux;

	adj->n = 0;
	adj->l = NULL;

    // locating and storing adjacent vertexes in "adj_vertexes"
    for (i = 0; i < graph_m->n; i++) {
		if (graph_m->matrix[vertex][i] != EMPTY) {
			adj->l = (int *) realloc(adj->l, sizeof(int) * (adj->n+1));
			adj->l[adj->n++] = i;
		}
    }

    // sorting vertexes
    for (i = 0; i < adj->n; i++) {
		for (j = i+1; j < adj->n; j++) {
			if (adj->l[i] > adj->l[j]) {
				aux = adj->l[i];
				adj->l[i] = adj->l[j];
				adj->l[j] = aux;
			}
		}
    }
    
	return adj;
}

void print_least_weighted_edge_m(GRAPH_M *graph_m) {
    int least, least_i, least_j;
    int i, j;

    // initializing, !!! assuming no other weight is greater than 9 !!!
    least = 10;
    
    for (i = 0; i < graph_m->n; i++) {
	for (j = 0; j < graph_m->n; j++) {
	    if (graph_m->matrix[i][j] != EMPTY && graph_m->matrix[i][j] < least) {
		least = graph_m->matrix[i][j];
		least_i = i;
		least_j = j;
	    }
	}
    }

    printf("%d %d\n", least_i, least_j);
}

void print_transpose_graph_m(GRAPH_M *graph_m) {
    int i, j;

    if (!graph_m->digraph) return;

    for (i = 0; i < graph_m->n; i++) {
	for (j = 0; j < graph_m->n; j++) {
	    if (graph_m->matrix[j][i] != EMPTY)
		printf("%d ", graph_m->matrix[j][i]);
	    else
		printf(". ");
	}

	printf("\n");
    }
}

void free_graph_m(GRAPH_M *graph_m) {
    int i;

    for (i = 0; i < graph_m->n; i++)
	free(graph_m->matrix[i]);
    
    free(graph_m->matrix);
    free(graph_m);
}

INT_ARR *source_vertex_graph_m(GRAPH_M *graph_m) {
	int i, j;
	INT_ARR *sources;

	sources = malloc(sizeof(INT_ARR));
	sources->l = NULL;
	sources->n = 0;

	for (i = 0; i < graph_m->n; i++) {
		for (j = 0; j < graph_m->n && !exists_edge_m(graph_m, j, i); j++);
			
		if (j < graph_m->n) {
			sources->l = realloc(sources->l, sizeof(int) * (sources->n+1));
			sources->l[sources->n++] = i;
		}
	}

	return sources;
}
