#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>
#include <stdio.h>
#include "tuple.h"

#define MAX_HEAP_SIZE 100
#define INF (unsigned int) -1 >> 1

typedef struct {
	TUPLE *h[MAX_HEAP_SIZE];
	int n;
} HEAP;

HEAP *create_heap();
int heap_empty(HEAP *);
void heap_insert(HEAP *, TUPLE *);
TUPLE *heap_search_by_vertex(HEAP *, int);
TUPLE *heap_pop(HEAP *);
void heap_update(HEAP *, int, int);
void heap_print(HEAP *);

#endif
