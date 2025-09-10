#include <stdio.h>
#include <stdlib.h>
#define NUM_ELEMENTS 10
#define MAX (NUM_ELEMENTS+1)
// We use an extra slot to distinguish between full or not

typedef struct {
	char Elems[MAX];
	int front, rear;
} C_Queue;

void init(C_Queue* Q);
int isEmpty(C_Queue Q);
int isFull(C_Queue Q);
char front(C_Queue Q);
char rear(C_Queue Q);
void enqueue(C_Queue* Q, char elem);
void dequeue(C_Queue* Q);
void read(C_Queue Q);

int main(void) {
	C_Queue Q;
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

char front(C_Queue Q) {
	char elem = '\0';
	if (!isEmpty(Q)) elem = Q.Elems[Q.front];
	return elem;
}

char rear(C_Queue Q) {
	char elem = '\0';
	if (!isEmpty(Q)) elem = Q.Elems[Q.rear];
	return elem;
}

void enqueue(C_Queue* Q, char elem) {
	if (!isFull(*Q)) {
		Q->rear = (Q->rear + 1) % MAX;
		Q->Elems[Q->rear] = elem;
	} else {
		printf("LIST IS FULL!\n");
	}
}

void dequeue(C_Queue* Q) {
	if (!isEmpty(*Q)) {
		Q->front = (Q->front + 1) % MAX;
	} else {
		printf("LIST IS EMPTY!\n");
	}
}

void read(C_Queue Q) {
	printf("\nQUEUE\n");
	while (!isEmpty(Q)) {
		printf("%c\n", front(Q));
		dequeue(&Q);
	}
}