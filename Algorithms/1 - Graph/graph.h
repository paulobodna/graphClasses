/*
 * =====================================================================================
 *
 *       Filename:  graph.h
 *
 *    Description:  matrix implementation of a graph
 *
 *        Version:  1.0
 *        Created:  12/03/2018 02:03:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Paulo Bodnarchuki, paulo.henrique.cruz@usp.br
 *         Nº USP:  9790944
 *
 * =====================================================================================
 */

#ifndef GRAPH_H
#define GRAPH_H

typedef struct graph GRAPH;
typedef struct vert VERT;
typedef struct arc ARC;

struct graph {
    bool type; // false = Dígrafo, true = grafo
    bool mode; // false = matrix, true = list 
    int v, a;
    int **m_adj;
    VERT **l_adj;
};

struct vert {
    ARC *arcs;
};

struct arc {
    int tip;
    int weight;
    ARC *next;
};
// Aloca um grafo, com v = vertices e arcos = arcs.
// Type: false = dígrafo; true = grafo
// mode: false = matrix; true = list
void create_graph(GRAPH **graph, int vertices, int arcs, bool type, bool mode);

// auxiliar da função add_arc
void add_aux(GRAPH *graph, int src, int dst, int weight);

// adiciona um arco de src para dst, com peso weight
void add_arc(GRAPH *graph, int src, int dst, int weight);

// verifica se existe algum arco de src para dst
bool verify_arc(GRAPH *graph, int src, int dst);

// verifica os vértices adjacente de src
void verify_adj(GRAPH *graph, int src);

// auxiliar da função remove_arc
void remove_aux(GRAPH *graph, int src, int dst);

// remove um arco existente de src para dst
void remove_arc(GRAPH *graph, int src, int dst);

// imprime um grafo, independete do tipo e modo (matrix ou lista)
void print_graph(GRAPH *graph);

// retorna a transposição de um grafo não-direcionado
GRAPH *transpose_graph(GRAPH *graph);

// encontra o arco de menor peso de um dado grafo
void minimum_arc(GRAPH *graph);

// desaloca toda a memória alocada
void destroy_graph(GRAPH **graph);

// realiza as configurações iniciais do grafo: nVertices, nArcos, tipo e modo
void set_graph(GRAPH **graph);

// Lê as operações da entrada padrão:
// IG: imprime grafo; VA: encontra vertices adjacentes;
// AA: adiciona arco; RA: remove arco
// IT: transpoe um grafo; MP: encontra o arco de menor peso
void read_op(GRAPH *graph);

#endif
