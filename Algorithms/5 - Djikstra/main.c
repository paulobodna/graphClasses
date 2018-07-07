/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  main
 *
 *        Version:  1.0
 *        Created:  03/04/2018 22:21:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Paulo Bodnarchuki, paulo.henrique.cruz@usp.br
 *         Nº USP:  9790944
 *
 * =====================================================================================
 */

#include <stdio.h>
#include "graph.h"


int main() {
    
    GRAPH *g;

    set_graph(&g);
    read_op(g);

    destroy_graph(&g);

    return 0;
}
