#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct {
	char *elemPtr;
	int count;
	int arrSize;
} L, *LIST;

void initializeList(LIST A) {
	A->elemPtr = (char*)malloc(sizeof(char) * MAX);
	if (A->elemPtr != NULL) {
		A->count = 0;
		A->arrSize = MAX;
	}
}

void insertFirst(LIST A, char x);
void insertLast(LIST A, char x);
void insert(LIST A, char x);
void print(LIST A) {
	for (int idx = 0; idx < A->count; idx++) printf("%c -> ", A->elemPtr[idx]);
	printf("\n");
}

int main(void) {
	LIST L = (LIST)malloc(sizeof(LIST));
	initializeList(L);	
	insertFirst(L, 'u');
	insertFirst(L, 's');
	insertFirst(L, 'c');
	print(L);
	
	return 0;
}

void insertFirst(LIST A, char x) {
	int idx = A->count - 1;
	for (; idx > 0; idx--) {
		A->elemPtr[idx] = A->elemPtr[idx-1];
	}
	A->elemPtr[0] = x;
	A->count++;
}