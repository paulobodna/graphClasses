/*
 * =====================================================================================
 *
 *       Filename:  queue.c
 *
 *    Description:  Queue implementation
 *
 *        Version:  1.0
 *        Created:  02/04/2018 14:12:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Paulo Bodnarchuki, paulo.henrique.cruz@usp.br
 *         Nº USP:  9790944
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


void create_queue(QUEUE **q) {

    (*q) = (QUEUE *) malloc (sizeof(QUEUE));
    (*q)->head = NULL;
    (*q)->tail = NULL;
    (*q)->size = 0;

    return;
}

void enqueue(QUEUE *q, int n) {
        if (q != NULL) {
            NODE *new = (NODE *) malloc (sizeof(NODE));
            if (new != NULL) {
                new->next = NULL;
                new->element = n;
                if (q->size == 0) {
                    q->head = new;
                } else {
                    q->tail->next = new;
                }
                q->tail = new;             
                q->size++;
            }
        }
}

int dequeue(QUEUE *q) {
        NODE *aux;
        int n = -1;

        if (q != NULL && !is_empty(q)) {
            aux = q->head;
            q->head = q->head->next;
            n = aux->element;
            free(aux);
            q->size--;
        }

        return n;
}

int is_empty(QUEUE *q) {
        return (q->size == 0);
}

void destroy_queue(QUEUE **q) {
        while ((*q)->size > 0) dequeue(*q);
        free(*q);
        *q = NULL;
}
