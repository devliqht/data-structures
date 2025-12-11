#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define EMPTY 63 // ascii for ?
#define DELETED 64 // ascii for @
#define INVALID -1
#define MAX 10

typedef char Dictionary[MAX];

void initDict(Dictionary D) {
	for (int idx = 0; idx < MAX; idx++) D[idx] = EMPTY;
}

void printDict(Dictionary D) {
	printf("\nDICTIONARY D: \n");
	for (int idx = 0; idx < MAX; idx++) {
		printf("[%d] >> %c\n", idx, D[idx]);
	}
}

int hash(char elem) {
	int hash = 0;
	char upper = toupper(elem);
	switch (upper) {
		case 'A':
			hash = 1;
			break;
		case 'B':
			hash = 4;
			break;
		case 'C':
		case 'D':
			hash = 9;
			break;
		case 'E':
			hash = 0;
			break;
		case 'F':
			hash = 3;
			break;
		case 'G':
			hash = 4;
			break;
		case 'H':
			hash = 3;
			break;
		default:
			hash = INVALID;
			break;
	}
	
	return hash;
}

void insertElement(Dictionary D, char elem) {
	int searchLen = 0;
	if (D[hash(elem)] == EMPTY || D[hash(elem)] == DELETED) {
		D[hash(elem)] = elem;
		printf("\n[LOG] Inserting %c >> searchLen: %d\n", elem, searchLen);
	} else {
		int idx;
		for (idx = hash(elem); D[idx] != EMPTY && D[idx] != DELETED; idx = (idx+1) % MAX) {}
		D[idx] = elem;
		searchLen = idx - ((hash(elem) + 1) % MAX);
		printf("\n[LOG] Inserting %c >> searchLen: %d\n", elem, searchLen);
	}
	
	printDict(D);
}

int findElem(Dictionary D, char elem) {
	int count = 0, idx;
	for (idx = hash(elem); D[idx] != EMPTY && D[idx] != elem && count < MAX; idx = (idx+1) % MAX, count++) {};

	return (count < MAX && hash(elem) != INVALID) ? idx : INVALID;
};

void deleteElem(Dictionary D, char elem) {
	int idx = findElem(D, elem);
	if (idx != INVALID) {
		D[idx] = DELETED;
		printf("\n[LOG] Deleting %c at index %d\n", elem, idx);
	} else {
		printf("\n[LOG] Failed to delete elem: element not found\n");
	}

	printDict(D);
}

int main(void) {
	Dictionary D;
	initDict(D);
	insertElement(D, 'A');
	insertElement(D, 'B');
	insertElement(D, 'C');
	insertElement(D, 'D');
	insertElement(D, 'E');
	insertElement(D, 'F');
	insertElement(D, 'G');
	insertElement(D, 'H');
	
	deleteElem(D, 'D');
	deleteElem(D, 'S');
	insertElement(D, 'D');
	return 0;
	
}