#include <stdio.h>
#include "int_arr.h"

int search_in_iarr(INT_ARR *arr, int key) {
	int i;

	for (i = 0; i < arr->n; i++) {
		if (arr->l[i] == key)
			return i;
	}

	return -1;
}

void print_iarr(INT_ARR *arr) {
	int i;
	
	for (i = 0; i < arr->n; i++)
		printf("%d ", arr->l[i]);
	printf("\n");

}
