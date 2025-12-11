#include <stdlib.h>
#include <stdio.h>
#define MAX (sizeof(unsigned char) * 8)
typedef unsigned char Set;

typedef struct {
	Set S;
	int count;
} SET;

void initSet (SET* Set) {
	Set->S = 0;
	Set->count = 0;
}

void displaySet(SET Set) {
	for (unsigned char bitmask = (1 << ((sizeof(char) * 8) - 1)); bitmask > 0; bitmask = bitmask >> 1) {
		printf("%d", ((Set.S & bitmask) == bitmask) ? 1: 0);
	}
	putchar('\n');
}

void insert(SET* Set, int pos) {
	if (pos < MAX && pos >= 0) {
		unsigned char bitmask = 1 << pos;
		Set->S = Set->S | bitmask;
		Set->count++;
	}
}

void delete(SET* Set, int pos) {
	if (pos < MAX && pos >= 0) {
		unsigned char bitmask = 1 << pos;
		Set->S = Set->S && ~bitmask;
		Set->count--;
	}
}

SET* UNION(SET* A, SET* B) {
	SET* C = (SET*)malloc(sizeof(SET));
	if (C != NULL) {
		initSet(C);
		C->S = A->S | B->S;
		unsigned char temp = C->S;
		while(temp) {
			C->count += temp & 1;
			temp >>= 1;
		}
	}
	return C;
}

int main(void) {
	SET S;
	initSet(&S);
	insert(&S, 1);
	insert(&S, 2);
	insert(&S, 3);
	insert(&S, 6);
	insert(&S, 7);
	displaySet(S);
	
	SET L;
	initSet(&L);
	insert(&L, 0);
	insert(&L, 5);
	insert(&L, 5);
	insert(&L, 6);
	insert(&L, 7);
	displaySet(L);
	
	SET* C = UNION(&S, &L);
	displaySet(*C);
	
	return 0;
}
