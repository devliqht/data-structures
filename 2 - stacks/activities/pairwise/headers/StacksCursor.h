#include <stdlib.h>
#include <stdio.h>

#define MAX 10

typedef struct {
	char data;
	int link;
} Node;

typedef struct {
	Node Nodes[MAX];
	int Avail;
} VirtualHeap;

typedef struct {
	VirtualHeap Elems;
	int top;
} Stack;

typedef int LIST;

void initVirtualHeap(VirtualHeap* VH) {
	// On initialize, all the nodes starting from the last one gets assigned their link value 
	// that is equal to the current idx - 1. e.g
	// MAX = 10 (10 nodes, 0-9) Nodes[9].link = 8, Nodes[8].link = 7, so on and so forth...
	for (int idx = MAX-1; idx >= 0; idx--) {
		VH->Nodes[idx].link = idx-1;
	}
	// Then sets the available Node to MAX - 1 (the first Node) *technically the last node on the list, 
	// but since we're starting from the last it is the first node.
	VH->Avail = MAX-1;
}

int allocSpace(VirtualHeap* VH) {
	// Declare a sentinel value
	int temp = -1;
	// If Avail is not -1 (List is NOT empty or FULL), sets temp to the Avail node, and then
	// reassigns avail to the link of previous avail node, basically "moving" forwards
	if (VH->Avail != -1) {
		temp = VH->Avail;
		VH->Avail = VH->Nodes[VH->Avail].link;
	}
	// Returns -1 (NULL in LinkedLists) if alloc failed, otherwise returns the avail node
	return temp;
}

void deallocSpace(VirtualHeap* VH, int idx) {
	// The purpose of this function is to free the Node at the index we gave.
	// We check first if index is within bounds and is equal or greater than 0, since we can use 0 as the index.
	if (idx < MAX-1 && idx >= 0) {
		// We assign the link of the given index to the current available node,
		// And then make the current index the available node.
		VH->Nodes[idx].link = VH->Avail;
		VH->Avail = idx;
	}
}

void initStack(Stack* S) {
	initVirtualHeap(&S->Elems);
	S->top = -1;
}

int isEmpty(Stack S) {
	return (S.top == -1) ? 1 : 0;
}

int isFull(Stack S) {
	return (S.top == MAX-1) ? 1 : 0;
}

void push(Stack* S, char elem) {
	LIST temp = allocSpace(&S->Elems);
	if (temp != -1) {
		S->Elems.Nodes[temp].data = elem;
		S->Elems.Nodes[temp].link = S->top;
		S->top = temp;
	}
}
