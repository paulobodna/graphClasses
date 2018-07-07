/*
 * =====================================================================================
 *
 *       Filename:  queue.h
 *
 *    Description:  Queue library
 *
 *        Version:  1.0
 *        Created:  02/04/2018 19:16:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Paulo Bodnarchuki, paulo.henrique.cruz@usp.br
 *         Nº USP:  9790944
 *
 * =====================================================================================
 */

#ifndef QUEUE_H
#define QUEUE_H

typedef struct node {
    struct node *next;
    int element;
} NODE;

typedef struct queue {
    NODE *head;
    NODE *tail;
    int size;
} QUEUE;


void create_queue(QUEUE **q);
void enqueue(QUEUE *q, int n);
int dequeue(QUEUE *q);
int is_empty(QUEUE *q);
void destroy_queue(QUEUE **q);


#endif
