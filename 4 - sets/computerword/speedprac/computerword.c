#include <stdlib.h>
#include <stdio.h>

#define MAX (sizeof(unsigned char) * 8) // We define max here as a 8 bits (since sizeof(unsigned char) returns 1 [1 byte] * 8)

typedef unsigned char WORD;

void initWord(unsigned char* w);
void insert(unsigned char* w, int e);
void delete(unsigned char* w, int e);
void display(unsigned char w);
void UNION(unsigned char* a, unsigned char* b);
void INTERSECTION(unsigned char* a, unsigned char* b);

int main(void) {
	WORD hey;
	initWord(&hey);
	
	insert(&hey, 1);
	insert(&hey, 3);
	display(hey);
	
	return 0;
}

void initWord(unsigned char* w) {
	*w = 0;
}

void insert(unsigned char* w, int e) {
	// We first check if element e is within bounds.
	if (e < MAX && e >= 0) {
		// We create a bit mask on the index of e. (e.g e = 4, this will create a bit pattern 00010000) to use for the ORing
		// Visualization: 
		// Start of B: 0000 0001
		// Shift 4 times
		// 0000 0010 << 1
		// 0000 0100 << 2
		// 0000 1000 << 3
		// 0001 0000 << 4
		unsigned char b = 1 << e;
		*w |= b;
	}
}

void display(unsigned char w) {
	// To display in a computer word, you set the bitmask to be at the left most side. For example,
	// An unsigned char has 8 bits. We put bitmask to 1 on the left most side which equates to 128.
	// We then AND operation the bitmask with the computer word. If the AND operations equates to the BITMASK, then that means the element exists on that bit.
	// Print 1. Otherwise print 0.
	unsigned char b = 1 << ((sizeof(unsigned char) * 8) - 1);
	for (int idx = 0; idx < MAX; idx++) {
		printf("%d%s", ((w&b) == b) ? 1 : 0, (b > (1 >> ((sizeof(unsigned char)*8) - 2))) ? "" : "\n");
		b >>= 1;
	}
	
	// unsigned char bc = 1 << ((sizeof(unsigned char) * 8) - 1);
	// for (int idx = 0; idx < MAX; idx++) {
	// 	printf("%d", ((w&b) == b) ? 1 : 0);
	// 	b >>= 1;
	// }
}