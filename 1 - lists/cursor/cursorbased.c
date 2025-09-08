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

typedef int List;

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

void display(List L, VirtualHeap VH) {
 	printf("LIST: ");
  
  	for (int idx = L; idx != -1; idx = VH.Nodes[idx].link){
   printf("%c%s", VH.Nodes[idx].data, (VH.Nodes[idx].link == -1) ? "\n" : ", ");
   }
   
   if (L == -1) {
   printf("LIST EMPTY\n");
   } else {
   printf("Available Node: %d\n", VH.Avail);
   }
}

void insertFirst(List *L, VirtualHeap* VH, char data) {
	// We first alloc space. This returns our available node. Returns -1 if the list is full.
	int temp = allocSpace(VH);
	if (temp != -1) {
		// If list is not full, assign the current available node data
		// and link to be the previous node
		VH->Nodes[temp].data = data;
		VH->Nodes[temp].link = *L;
		*L = temp;
	}
}

void insertLast(List *L, VirtualHeap* VH, char data) {
	int temp = allocSpace(VH);
	// Check if there's available space
	if (temp != -1) {
		// If there is, declare a variable trav and let it point to the same address as L, basically
		// the current head of the list.
		int* trav;
		// Traverse the list until it's not null. Assign trav the address of the current node's link.
		// The loop stops when the link is -1. 
		// This is similar to PPN traversal in LinkedList.
		// It's one condition since we always reach the end.
  		for(trav = L; (*trav) != -1; trav = &(VH->Nodes[*trav].link)) {}
    
    	// Assign the last node with the data, and set its link to -1 (end of list)
     	// e.g Assuming we have available node at index 4 (returned by allocSpace), we set that node
      	// to the data we gave, and link to -1
    	VH->Nodes[temp].data = data;
     	VH->Nodes[temp].link = -1;
      
      	// then we assign the LINK (this *trav is 'returned' by the for loop)
       	// to temp (the current node), basically inserting last
      	*trav = temp;
	}
}

int locate(List L, VirtualHeap VH, char data) {
	int idx;
	for (idx = L; idx != -1 && VH.Nodes[idx].data != data; idx = VH.Nodes[idx].link) {};
	return (idx == -1) ? -1 : idx;
}

int main(void) {
	VirtualHeap vh;
	List L = -1;
	initVirtualHeap(&vh);
	
	display(L, vh);
	insertFirst(&L, &vh, 'u');
	insertFirst(&L, &vh, 's');
	insertFirst(&L, &vh, 'c');
	insertFirst(&L, &vh, 't');
	insertFirst(&L, &vh, 'c');
	display(L, vh);
	
	insertLast(&L, &vh, 'm');
	display(L, vh);
	
	int loc = locate(L, vh, 'c');
	printf(loc == -1 ? "Element not found.\n" : "Element found: %c\n", vh.Nodes[loc].data);
	
	int loc2 = locate(L, vh, 'n');
	printf(loc2 == -1 ? "Element not found.\n" : "Element found: %c\n", vh.Nodes[loc2].data);
	
	
	return 0;
}