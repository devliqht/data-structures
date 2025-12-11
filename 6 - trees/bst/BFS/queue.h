#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#define NUM_ELEMENTS 20
#define MAX (NUM_ELEMENTS+1)
// We use an extra slot to distinguish between full or not

typedef struct node {
	int elem;
	struct node* left;
	struct node* right;
} *BST;

typedef struct {
	BST Elems[MAX];
	int front, rear;
} C_Queue;

void init(C_Queue* Q);
int isEmpty(C_Queue Q);
int isFull(C_Queue Q);
BST front(C_Queue Q);
BST rear(C_Queue Q);
void enqueue(C_Queue* Q, BST elem);
BST dequeue(C_Queue* Q);
void read(C_Queue Q);

#endif