/*
 * =====================================================================================
 *
 *       Filename:  graph.c
 *
 *    Description:  graph implementation
 *
 *        Version:  1.0
 *        Created:  12/03/2018 02:34:23
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

void create_graph(GRAPH **graph, int vertices, int arcs, bool type, bool mode) {
    (*graph) = (GRAPH *) malloc(sizeof(GRAPH));
    
    (*graph)->v = vertices;
    (*graph)->a = arcs;
    (*graph)->type = type;
    (*graph)->mode = mode;

    if((*graph)->mode == false) {  // se for matriz
        (*graph)->m_adj = (int **) malloc(vertices * sizeof(int *));
        for(int i = 0; i < vertices; i++) {
            (*graph)->m_adj[i] = (int *) malloc(vertices * sizeof(int));
            for(int j = 0; j < vertices; j++) {
                (*graph)->m_adj[i][j] = -1;
            }
        }
    } else { // se for lista
        (*graph)->l_adj = (VERT **) malloc (vertices * sizeof(VERT *));
        for(int i = 0; i < vertices; i++) {
            (*graph)->l_adj[i] = (VERT *) malloc(sizeof(VERT));
            (*graph)->l_adj[i]->arcs = NULL;
        }
    }
}

void add_aux(GRAPH *graph, int src, int dst, int weight) {
    ARC *aresta = (ARC *) malloc(sizeof(ARC));
    aresta->tip = dst;
    aresta->weight = weight;

    if(graph->l_adj[src]->arcs == NULL) {
        aresta->next = NULL;
        graph->l_adj[src]->arcs = aresta;
    } else {
        ARC *aux = graph->l_adj[src]->arcs;
        if(dst < aux->tip) {
            aresta->next = aux;
            graph->l_adj[src]->arcs = aresta;
        } else {
            while(aux->next != NULL && aux->next->tip < dst) aux = aux->next;
            aresta->next = aux->next;
            aux->next = aresta;
        }
    }
}

void add_arc(GRAPH *graph, int src, int dst, int weight) {
    if(graph->mode == false) {  // se for matriz
        graph->m_adj[src][dst] = weight;
        if(graph->type == true) {
            graph->m_adj[dst][src] = weight;
        }
    } else { // se for lista
        add_aux(graph, src, dst, weight);
        if(graph->type == true && src != dst) {
            add_aux(graph, dst, src, weight);
        }
    }
}

bool verify_arc(GRAPH *graph, int src, int dst) {
    if(graph->mode == false) {  // se for matriz
        if(graph->m_adj[src][dst] == -1) return false;
        else return true;
    } else { // se for lista
        ARC *aux = graph->l_adj[src]->arcs;
        while(aux != NULL && aux->tip <= dst) {
            if(aux->tip == dst) return true;
            aux = aux->next;
        }
        return false;
    }
}

void verify_adj(GRAPH *graph, int src) {
    if(graph->mode == false) {  // se for matriz
        for(int i = 0; i < graph->v; i++) {
            if(graph->m_adj[src][i] != -1) {
                printf("%d ", i);
            }
        }
    } else { // se for lista
        ARC *aux = graph->l_adj[src]->arcs;
        while(aux != NULL) {
            printf("%d ", aux->tip);
            aux = aux->next;
        }
    }
    printf("\n");
}

void remove_aux(GRAPH *graph, int src, int dst) {
    
    ARC *aux_a = graph->l_adj[src]->arcs;

    if(aux_a->tip == dst) {
        graph->l_adj[src]->arcs = aux_a->next;
        free(aux_a);
    } else { // se for lista
        while(aux_a->next->tip != dst) {
            aux_a = aux_a->next;   
        }
        ARC *aux_b = aux_a->next;
        aux_a->next = aux_b->next;
        free(aux_b);
    }

    return;
}

void remove_arc(GRAPH *graph, int src, int dst) {
    if(graph->mode == false) {  // se for matriz
        graph->m_adj[src][dst] = -1;
        if(graph->type == true) {
            graph->m_adj[dst][src] = -1;
        }
    } else { // se for lista
        remove_aux(graph, src, dst);
        if(graph->type == true && src != dst) {
            remove_aux(graph, dst, src);
        }
    }
}

int print_path(int *previous, int src, int dst) {
    
    if(src == dst) {
        printf("%d ", dst);
        return 1;
    } else if(previous[dst] != -1 && print_path(previous, src, previous[dst])) {
        printf("%d ", dst);
    } else return 0;
}

void breadth_search(GRAPH *graph, int src, int dst) {
    
    if(src == dst) {
        printf("%d\n", src);
        return;
    }
    
    int *color = (int *) malloc (graph->v * sizeof(int)); // 0 = branca; 1 = cinza; 2 = preta
    int *dist = (int *) malloc (graph->v * sizeof(int));
    int *previous = (int *) malloc (graph->v * sizeof(int));
    QUEUE *q;
    create_queue(&q);

    for(int i = 0; i < graph->v; i++) {
        color[i] = 0;
        dist[i] = -1;
        previous[i] = -1;
    }

    color[src] = 1;
    dist[src] = 0;
    enqueue(q, src);

    int u;
    while(!is_empty(q)) {
        u = dequeue(q);
        for(int i = 0; i < graph->v; i++) {
            if(i != u && graph->m_adj[u][i] != -1) {
                if(color[i] == 0) {
                    color[i] = 1;
                    dist[i] = dist[u] + 1;
                    previous[i] = u;
                    enqueue(q, i);
                }
            }
        }
        color[u] = 2;
    }

    print_path(previous, src, dst);
    printf("\n");

    free(color);
    free(dist);
    free(previous);
    destroy_queue(&q);
    return;
}

void visit(GRAPH *graph, int u, int *color, int *previous, int *gray, int *black, int *timestamp) {
    
    color[u] = 1;
    gray[u] = *timestamp;
    (*timestamp)++;
    for(int i = 0; i < graph->v; i++) {
        if(graph->m_adj[u][i] != -1) {
            if(color[i] == 0) {
                previous[i] = u;
                visit(graph, i, color, previous, gray, black, timestamp);
            }
        }
    }
    color[u] = 2;
    black[u] = *timestamp;
    (*timestamp)++;

    return;
}

void depth_search(GRAPH *graph, int src, int dst) {
    if(src == dst) {
        printf("%d\n", src);
        return;
    }
    
    int *color = (int *) malloc (graph->v * sizeof(int)); // 0 = branca; 1 = cinza; 2 = preta
    int *previous = (int *) malloc (graph->v * sizeof(int));
    int *gray = (int *) malloc (graph->v * sizeof(int));
    int *black = (int *) malloc (graph->v * sizeof(int));
    int timestamp = 0;

    for(int i = 0; i < graph->v; i++) {
        color[i] = 0;
        previous[i] = -1;
        gray[i] = -1;
        black[i] = -1;
    }
    
    visit(graph, src, color, previous, gray, black, &timestamp);
    for(int i = 0; i < graph->v; i++) {
        if(color[i] == 0)
            visit(graph, i, color, previous, gray, black, &timestamp);
    }

    print_path(previous, src, dst);
    printf("\n");

    free(color);
    free(previous);
    free(gray);
    free(black);
    return;
}

void print_graph(GRAPH *graph) {
    
    if(graph->mode == false) {  // se for matriz
        for(int i = 0; i < graph->v; i++) {
            for(int j = 0; j < graph->v; j++) {
                if(graph->m_adj[i][j] != -1) {
                    printf("%d ", graph->m_adj[i][j]);
                } else printf(". ");
            }
            printf("\n");
        }
    } else { // se for lista
        ARC *aux;
        for(int i = 0; i < graph->v; i++) {
            printf("%d. ", i );
            aux = graph->l_adj[i]->arcs;
            while(aux != NULL) {
                printf("%d(%d) ", aux->tip, aux->weight);
                aux = aux->next;
            }
            printf("\n");
        }
    }
}

GRAPH *transpose_graph(GRAPH *graph) {
    GRAPH *aux;

    create_graph(&aux, graph->v, graph->a, graph->type, graph->mode);

    for(int i = 0; i < graph->v; i++) {
        if(graph->mode == false) {  // se for matriz
            for(int j = 0; j < graph->v; j++) {
                aux->m_adj[i][j] = graph->m_adj[j][i];
            }
        } else { // se for lista
            ARC *a = graph->l_adj[i]->arcs;
            while(a != NULL) {
                add_arc(aux, a->tip, i, a->weight);
                a = a->next;
            }
        }
    }

    return aux;
}

void minimum_arc(GRAPH *graph) {
    int minimum = -1;
    int src, dst;

    for(int i = 0; i < graph->v; i++) {
        if(graph->mode == false) {  // se for matriz
            for(int j = 0; j < graph->v; j++) {
                if(graph->m_adj[i][j] > -1 && (minimum == -1 || graph->m_adj[i][j] < minimum)) {
                    minimum = graph->m_adj[i][j];
                    src = i;
                    dst = j;
                }
            }
        } else { // se for lista
            ARC *aux = graph->l_adj[i]->arcs;
            while(aux != NULL) {
                if(minimum == -1 || aux->weight < minimum) {
                    minimum = aux->weight;
                    src = i;
                    dst = aux->tip;
                }
                
                aux = aux->next;
            }
        }
    }

    if(minimum != -1) {
        printf("%d %d\n", src, dst);
    } else {
        printf("Nenhuma aresta no grafo\n");
    }
}

void destroy_graph(GRAPH **graph) {
    if((*graph)->mode == false) {  // se for matriz
        for(int i = 0; i < (*graph)->v; i++) {
            free((*graph)->m_adj[i]);
        }
        free((*graph)->m_adj);
    } else { // se for lista
        ARC *arc, *aux;
        for(int i = 0; i < (*graph)->v; i++) {
            arc = (*graph)->l_adj[i]->arcs;
            while(arc != NULL) {
                aux = arc->next;
                free(arc);
                arc = aux;
            }
            (*graph)->l_adj[i]->arcs = NULL;
            free((*graph)->l_adj[i]);
            (*graph)->l_adj[i] = NULL;
        }
        free((*graph)->l_adj);
        (*graph)->l_adj = NULL;
    }
    free(*graph);
    (*graph) = NULL;
}

void set_graph(GRAPH **graph) {
    
//    char type, mode;
//    bool t, m;
    int vert, arc, src, dst, weight;
    
//    scanf("%c %c", &type, &mode);
//    getchar();
    scanf("%d", &vert);
    scanf("%d", &arc);
    
//    if(type == 'G') t = true;
//    else t = false;
//    
//    if(mode == 'L') m = true;
//    else m = false;
    
    create_graph(graph, vert, arc, false, false);
    for(int i = 0; i < arc; i++) {
        scanf("%d", &src);
        scanf("%d", &dst);
//        scanf("%d", &weight);
        if(verify_arc(*graph, src, dst)) {
            remove_arc(*graph,src,dst);
        }
        add_arc(*graph, src, dst, 1);
    }

//    print_graph(*graph);

    return;
}

void read_op(GRAPH *graph) {
    
    int src, dst;

    while(scanf("%d", &src) == 1) {
        scanf("%d", &dst);
//        breadth_search(graph, src, dst);
        depth_search(graph, src, dst);
    }
        
    return;
}
