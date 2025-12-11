#include "queue.h"

void init(C_Queue* Q) {
	Q->front = 0;
	Q->rear = MAX-1;
}

int isEmpty(C_Queue Q) {
	return ((Q.rear + 1) % (MAX) == Q.front) ? 1 : 0;
}

int isFull(C_Queue Q) {
	return ((Q.rear + 2) % (MAX) == Q.front) ? 1 : 0;
}

BST front(C_Queue Q) {
	BST elem = NULL;
	if (!isEmpty(Q)) elem = Q.Elems[Q.front];
	return elem;
}

BST rear(C_Queue Q) {
	BST elem = NULL;
	if (!isEmpty(Q)) elem = Q.Elems[Q.rear];
	return elem;
}

void enqueue(C_Queue* Q, BST elem) {
	if (!isFull(*Q)) {
		Q->rear = (Q->rear + 1) % MAX;
		Q->Elems[Q->rear] = elem;
	} else {
		printf("LIST IS FULL!\n");
	}
}

BST dequeue(C_Queue* Q) {
	BST retval = NULL;
	if (!isEmpty(*Q)) {
		retval = Q->Elems[Q->front];
		Q->front = (Q->front + 1) % MAX;
	} else {
		printf("LIST IS EMPTY!\n");
	}
	return retval;
}

void read(C_Queue Q) {
	printf("\nQUEUE\n");
	while (!isEmpty(Q)) {
		printf("%c\n", front(Q)->elem);
		dequeue(&Q);
	}
}