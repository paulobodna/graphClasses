#include <stdlib.h>
#include "tuple.h"

TUPLE *new_tuple(int vertex, int weight) {
	TUPLE *newTuple = malloc(sizeof(TUPLE));

	newTuple->vertex = vertex;
	newTuple->weight = weight;
	
	return newTuple;
}
