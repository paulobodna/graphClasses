/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  PRIM implementation
 *
 *        Version:  1.0
 *        Created:  14/05/2018 15:34:23
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Paulo Bodnarchuki, paulo.henrique.cruz@usp.br
 *         Nº USP:  9790944
 *
 * =====================================================================================
 */

#include <stdio.h>
#include "grafo-matriz.h"
#include "int_arr.h"
#include "heap.h"

INT_ARR *prim(GRAPH_M *graph, int startingPoint) {
	int i;
	int u, v; // representando vertices
	INT_ARR *P = (INT_ARR *) malloc(sizeof(INT_ARR)); // predecessor
	INT_ARR *A = (INT_ARR *) malloc(sizeof(INT_ARR)); // MST
	HEAP *heap = create_heap(); // fila de prioridades

	A->n = 0;
	A->l = NULL;

	P->n = graph->n;
	P->l = malloc(sizeof(int) * P->n);
	
	for (i = 0; i < graph->n; i++) {
		P->l[i] = EMPTY;
		heap_insert(heap, new_tuple(i, INF));
	}

	heap_update(heap, startingPoint, 0);

	while (!heap_empty(heap)) {
		TUPLE *t = heap_pop(heap); // t = aux para dar free;
		u = t->vertex;
		A->l = realloc(A->l, sizeof(int) * (A->n+1));
		A->l[A->n++] = u;

		INT_ARR *adj = adj_vertexes_m(graph, u);
		for (i = 0; i < adj->n; i++) {
			v = adj->l[i];
			if ((search_in_iarr(A, v) == -1) && (graph->matrix[u][v] < heap_search_by_vertex(heap, v)->weight)) {
				heap_update(heap, v, graph->matrix[u][v]);
				P->l[v] = u;
			}
		}

		free(adj->l);
		free(adj);
		free(t);
	}

	for (i = 0; i < A->n; i++) {
		u = P->l[A->l[i]];
		v = A->l[i];

		// imprime: (<menor>, <maior>)
		if (u != EMPTY) {
			if (u < v)
				printf("(%d,%d) ", u, v);
			else
				printf("(%d,%d) ", v, u);
		}
	} printf("\n");

	free(A->l);
	free(A);
	free(P->l);
	free(P);
	free(heap);

	return P;
}

int main(int argc, char *argv[]) {
	int i;
	int n_vertexes, n_edges;
	int vertex_a, vertex_b, weight;
	GRAPH_M *graph;
    int iterations = 0;

	scanf("%d %d", &n_vertexes, &n_edges);

	graph = create_graph_m(n_vertexes, 0); // grafo nao direcionado

	for (i = 0; i < n_edges; i++) {
		scanf("%d %d %d", &vertex_a, &vertex_b, &weight);
        iterations++;
		insert_new_edge_m(graph, vertex_a, vertex_b, weight);
	}

	prim(graph, 0);

	free_graph_m(graph);

	return 0;
}
