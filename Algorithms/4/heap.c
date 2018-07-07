#include "heap.h"

#define parent(n) (n-1)/2
#define left_child(n) ((n+1)*2)-1
#define right_child(n) ((n+1)*2)

static void swap(TUPLE **a, TUPLE **b) {
	TUPLE *aux;

	aux = *a;
	*a = *b;
	*b = aux;
}

// min heap
HEAP *create_heap() {
	int i;
	HEAP *heap = (HEAP *) malloc(sizeof(HEAP));
	
	heap->n = 0;	
	for (i = 0; i < MAX_HEAP_SIZE; i++) {
		heap->h[i] = NULL;
	}
	
	return heap;
}

int heap_empty(HEAP *heap) {
	return heap->n == 0;
}

static void min_heapify(HEAP *heap, int pos) {
	int left, right, smallest;

	left = left_child(pos);
	right = right_child(pos);
	smallest = pos;

	// se o peso for igual, pega o que tem menor vértice
	if (left < heap->n && (heap->h[left]->weight < heap->h[smallest]->weight ||
						   (heap->h[left]->weight == heap->h[smallest]->weight &&
							heap->h[left]->vertex < heap->h[smallest]->vertex))) {
			smallest = left;
	}
	if (right < heap->n && (heap->h[right]->weight < heap->h[smallest]->weight ||
						   (heap->h[right]->weight == heap->h[smallest]->weight &&
							heap->h[right]->vertex < heap->h[smallest]->vertex))) {
		smallest = right;
	}

	if (smallest != pos) {
		swap(&heap->h[pos], &heap->h[smallest]);
		min_heapify(heap, smallest);
	}
}

static void build_min_heap(HEAP *heap) {
	int i;


	for (i = heap->n/2-1; i >= 0; i--) {
		min_heapify(heap, i);
	}
}

void heap_insert(HEAP *heap, TUPLE *e) {
	if (heap->n >= MAX_HEAP_SIZE) {
		printf("heap full\n");
		return;
	}

	heap->h[heap->n++] = e;

	build_min_heap(heap);
}

TUPLE *heap_search_by_vertex(HEAP *heap, int v) {
	int i;

	for (i = 0; i < heap->n; i++) {
		if (heap->h[i]->vertex == v)
			return heap->h[i];
	}

	return NULL;
}

void heap_update(HEAP *heap, int v, int newWeight) {
	TUPLE *tuple = heap_search_by_vertex(heap, v);
	tuple->weight = newWeight;

	build_min_heap(heap);
}

// remove e retorna o topo da heap
TUPLE *heap_pop(HEAP *heap) {
	TUPLE *removedEdge;

	if (heap->n == 0) {
		printf("heap empty");
		return NULL;
	}
	
	removedEdge = heap->h[0];
	heap->h[0] = heap->h[heap->n-1];
	heap->h[--heap->n] = NULL;

	build_min_heap(heap);

	return removedEdge;
}

// para debug
void heap_print(HEAP *heap) {
	int i;

	for (i = 0; i < heap->n; i++) {
		printf("%d: ", heap->h[i]->vertex);
		if (heap->h[i]->weight == INF)
			printf("x |");
		else
			printf("%d |", heap->h[i]->weight);
	}
	printf("\n");
}
