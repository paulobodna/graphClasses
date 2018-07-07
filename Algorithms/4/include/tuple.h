#ifndef TUPLE_H
#define TUPLE_H

typedef struct {
	int vertex;
	int weight;
} TUPLE;

TUPLE *new_tuple(int, int);

#endif
