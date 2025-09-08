#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct {
	char elem[MAX];
	int count;
} L;

void insertLastUnique(L *A, char x) {
	int idx;
	for (idx = 0; idx < A->count && A->elem[idx] != x; idx++) {}
	if (idx == A->count && A->count < MAX) {
		A->elem[A->count++] = x;
	}
}

void printADTList(L list) {
	for (int idx = 0; idx < list.count; idx++) {
		printf("%c -> ", list.elem[idx]);
	}
	printf("\nCount: %d \n", list.count);
}

int main(void) {
	L list = {{}, 0};

	insertLastUnique(&list, 'u');
	insertLastUnique(&list, 's');
	insertLastUnique(&list, 'c');
	insertLastUnique(&list, 'c');
	insertLastUnique(&list, 'c');
	printADTList(list);
	
	
	
	return 0;
}