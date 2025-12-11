#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct {
	int elems[MAX];
	int front, rear;
} Queue;

void initQueue(Queue* q);
int isFull(Queue q);
int isEmpty(Queue q);
int front(Queue q);
void enqueue(Queue* q, int elem);
int dequeue(Queue* q);


int main(void) {
	
	return 0;
}

void initQueue(Queue* q) {
	q->front = 0;
	q->rear = 0;
}

int isFull(Queue q) {
	return (q.rear == MAX-1) ? 1:0;
}

int isEmpty(Queue q) {
	return (q.front == q.rear) ? 1:0;
}

