#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#define MAX 10

typedef struct {
	int elems[MAX];
	int rear;
	int front;
} Queue;

void initialize(Queue *);
void sortQueue(Queue *);
void enqueue(Queue *, int);
int dequeue(Queue *);
void read(Queue);
int size(Queue);

int main() {
    int n;
    printf("Elems in queue: ");
    scanf("%d", &n);

	Queue Q;
	initialize(&Q);

    int input;

    for(int i = 0; i < n ; i++) {
        scanf("%d", &input);
        enqueue(&Q, input);
    }
    
    sortQueue(&Q);

   read(Q);
}

void initialize(Queue *Q) {
	Q->front = 0;
	Q->rear = MAX - 1;
}

int size(Queue Q) {
	return (Q.rear - Q.front + MAX + 1) % MAX;
}

bool isEmpty(Queue Q) {
	return (Q.rear + 1) % MAX == Q.front;
}

bool isFull(Queue Q) {
	return (Q.rear + 2) % MAX == Q.front;
}

void enqueue(Queue *Q, int x) {
	if(!isFull(*Q)) {
		Q->rear = (Q->rear + 1) % MAX;
		Q->elems[Q->rear] = x;
	}
}

void sortQueue(Queue *Q) { 
	Queue temp;
	Queue ordered;
	initialize(&temp);
	initialize(&ordered);

	while (!isEmpty(*Q)) {
		int min = INT_MAX;
		int minCount = 0;
		while (!isEmpty(*Q)) {
			int tempData = dequeue(Q);
			if (tempData < min) {
				min = tempData;
				minCount = 1;
			} else if (tempData == min) {
				minCount++;
			}
			enqueue(&temp, tempData);
		}
		while (!isEmpty(temp)) {
			int val = dequeue(&temp);
			if (val != min) enqueue(Q, val);
		}
		
		for (int idx = 0; idx < minCount; idx++) enqueue(&ordered, min);
	}
	while (!isEmpty(ordered)) enqueue(Q, dequeue(&ordered));
}

int dequeue(Queue *Q) {
	int temp = -1;
	if(!isEmpty(*Q)) {
		temp = Q->elems[Q->front];
		Q->front = (Q->front + 1) % MAX;
	}
	return temp;
}

void read(Queue Q) {
	if(!isEmpty(Q)) {
		int i;
		int n = size(Q);
        printf("Sorted Queue: ");
		for(i = 0; i < n; i++) {
			int temp = Q.elems[Q.front];
			Q.front = (Q.front + 1) % MAX;
			printf("%d ", temp);
		}
	}
}
