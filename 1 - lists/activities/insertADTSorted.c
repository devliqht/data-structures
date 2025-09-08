#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct {
	int elem[MAX];
	int count;
} A;

void insertADTSorted(A *list, int num) {
	int idx, jdx;
	for (idx = 0; idx < list->count && num > list->elem[idx]; idx++) {};
	if (list->count < MAX) {
		for (jdx = list->count++; jdx > idx; jdx--) {
			list->elem[jdx] = list->elem[jdx-1];
		}
		list->elem[idx] = num;
	}
}

void printADTList(A list) {
	for (int idx = 0; idx < list.count; idx++) {
		printf("%d -> ", list.elem[idx]);
	}
	printf("\nCount: %d \n", list.count);
}

int main(void) {
	A ADT = {{24, 11, 38, 49, 16, 7, 21}, 7};
	printADTList(ADT);
	insertADTSorted(&ADT, 9);
	printADTList(ADT);
	insertADTSorted(&ADT, 7);
	printADTList(ADT);
	insertADTSorted(&ADT, 100);
	printADTList(ADT);
	
}