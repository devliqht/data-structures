#include <stdlib.h>
#include <stdio.h>
#define MAX 10

typedef struct {
	char FName[24];
	char LName[16];
	char MI;
	int age;
} StudType;

typedef struct {
	StudType stud;
	int link;
} Node;

typedef struct {
	Node Nodes[MAX];
	int Avail;
} VirtualHeap;

typedef int List;

void initVirtualHeap(VirtualHeap *VH);
void allocSpace(VirtualHeap *VH);
void deallocSpace(VirtualHeap *VH, int idx);
void initList(List* L);
void printList(VirtualHeap* VH, List* L);

void addStudentFirst(VirtualHeap* VH, List* L, StudType stud);
void addLastFirst(VirtualHeap* VH, List* L, StudType stud);

int main(void) {
	VirtualHeap VH;
	List L = -1;
	return 0;
}

void initVirtualHeap(VirtualHeap *VH) {
	for (int idx = MAX-1; idx >= 0; idx--) {
		VH->Nodes[idx].link = idx-1;
	}
	VH->Avail = MAX-1;
}

void allocSpace(VirtualHeap* VH) {
	
}