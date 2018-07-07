#ifndef INT_ARR_H
#define INT_ARR_H

typedef struct {
	int *l;
	int n;
} INT_ARR;

int search_in_iarr(INT_ARR *, int);
void print_iarr(INT_ARR *);

#endif
