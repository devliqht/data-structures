#include <stdio.h>
#include <stdlib.h>
#define MAX 10
typedef struct {
	int Elems[MAX];
	int count;
} SET;

void initSet(SET* Set);
void populateSet(SET* Set, int option);
void printSet(SET Set);

void insert(SET* Set, int elem);
void delete(SET* Set, int elem);

SET UNION(SET A, SET B);
SET Intersection(SET A, SET B);
SET Difference(SET A, SET B);

int main(void) {
	SET S, A;
	initSet(&S);
	initSet(&A);
	populateSet(&S, 1);
	populateSet(&A, 0);
	printSet(S);
	printSet(A);
	
	SET D = UNION(S, A);
	printSet(D);
	
	return 0;
}

void initSet(SET* Set) {
	Set->count = 0;
}

void populateSet(SET* Set, int option) {
	int temp1[5] = { 21, 5, 9, 8, 6 };
	int temp2[5] = { 5, 11, 4, 21, 6 };
	
	for (int idx = 0; idx < 5; idx++) Set->Elems[Set->count++] = (option) ? temp1[idx] : temp2[idx];
}

void printSet(SET Set) {
	printf("{ ");
	for (int idx = 0; idx < Set.count; idx++) printf("%d %s", Set.Elems[idx], (idx < Set.count-1) ? ", " : "}\n");
}

void insert(SET* Set, int elem) {
	int idx;
	for (idx = 0; idx < Set->count && elem != Set->Elems[idx]; idx++) {}
	
	if (idx == Set->count && Set->count < MAX) {
		Set->Elems[idx] = elem;
		Set->count++;
	}
}

// SET UNION(SET A, SET B);
// SET Intersection(SET A, SET B);
// SET Difference(SET A, SET B);


SET UNION(SET A, SET B) {
	SET temp = A; 
	for (int idx = 0; idx < B.count; idx++) {
		insert(&temp, B.Elems[idx]);
		printf("temp: %d\n", temp.Elems[idx]);
	}
	
	return temp;
}