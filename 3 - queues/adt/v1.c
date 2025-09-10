#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
	char Elems[MAX];
	int front, rear;
} Queue;

void init(Queue* Q);
int isEmpty(Queue Q);
int isFull(Queue Q);
char front(Queue Q);
char rear(Queue Q);
void enqueue(Queue* Q, char elem);
void dequeue(Queue* Q);
void read(Queue Q);

int main(void) {
	Queue Q;
	init(&Q);
	enqueue(&Q, 'u');
	enqueue(&Q, 's');
	enqueue(&Q, 'c');
	printf("front: %d\n", Q.front);
	printf("rear: %d\n", Q.rear);
	read(Q);
	
	enqueue(&Q, 't');
	enqueue(&Q, 'c');
	enqueue(&Q, 'm');
	enqueue(&Q, 'e');
	enqueue(&Q, 'o');
	enqueue(&Q, 'w');

	enqueue(&Q, 'm');
	read(Q);
	printf("front: %d\n", Q.front);
	printf("rear: %d\n", Q.rear);
	
	enqueue(&Q, 'a');
	enqueue(&Q, 't');
	
	dequeue(&Q);
	dequeue(&Q);
	read(Q);
	
	enqueue(&Q, 'a');
	enqueue(&Q, 't');
	enqueue(&Q, 'e');
	read(Q);
	return 0;
}

void init(Queue* Q) {
	Q->front = 0;
	Q->rear = -1;
}

int isEmpty(Queue Q) {
	return (Q.rear < Q.front) ? 1 : 0;
}

int isFull(Queue Q) {
	return (Q.rear == MAX - 1) ? 1 : 0;
}

char front(Queue Q) {
	return (!isEmpty(Q)) ? Q.Elems[Q.front] : '\0';
}

char rear(Queue Q) {
	return (!isEmpty(Q)) ? Q.Elems[Q.front] : '\0';
}

void enqueue(Queue* Q, char elem) {
	if (!isFull(*Q)) {
		Q->Elems[++Q->rear] = elem;
	} else {
		printf("QUEUE FULL!\n");
	}
}

void dequeue(Queue* Q) {
	if (!isEmpty(*Q)) {
		Q->front++;
	} else {
		printf("QUEUE EMPTY!");
	}
}

void read(Queue Q) {
	printf("\nQUEUE\n");
	while (!isEmpty(Q)) {
		printf("%c\n", front(Q));
		dequeue(&Q);
	}
}