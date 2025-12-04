#include <stdio.h>
#include <stdlib.h>

#define VHSIZE 50

typedef struct {
    int data;
} Element;

typedef struct {
    Element elem;
    int next;
} Node;

typedef struct {
    Node VHNode[VHSIZE];
    int avail;
} VHeap;

typedef int Stack;  // index of top element


/*************************************/
/*           YOUR TASKS              */
/*************************************/
// --- CB functions --- //
void initVHeap(VHeap *VH);
int allocSpace(VHeap *VH);
void freeSpace(VHeap *VH, int idx);

// --- Stack functions ---
void initStack(Stack *S);
void push(VHeap *VH, Stack* S, int data);
void pop(VHeap *VH, Stack* S);
void insertSorted(VHeap *VH, Stack *S, int data);
void printStack(VHeap VH, Stack S);

// --- Main program ---
int main() {
    VHeap VH;
    Stack S;
    int N, val;

    initVHeap(&VH);
    initStack(&S);

    printf("Enter size: ");
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &val);
        // push(&VH, &S, val);
        insertSorted(&VH, &S, val);
    }

    printStack(VH, S);

    return 0;
}

void initVHeap(VHeap *VH) {
    for (int idx = VHSIZE-1; idx >= 0; idx--) {
        VH->VHNode[idx].next = idx-1;
    }
    VH->avail = VHSIZE - 1;
}

int allocSpace(VHeap *VH) {
    int temp = -1;
    if (VH->avail != -1) {
    	temp = VH->avail;
     	VH->avail = VH->VHNode[temp].next;
    }
    return temp;	
}

void freeSpace(VHeap *VH, int idx) {
    if (idx < VHSIZE-1 && idx >= 0) {
    	VH->VHNode[idx].next = VH->avail;
     	VH->avail = idx;
    }
}

// --- Stack functions ---
void initStack(Stack *S) {
	(*S) = -1;
}

void push(VHeap *VH, Stack *S, int data) {
	int node = allocSpace(VH);
	if (node != -1) {
		VH->VHNode[node].elem.data = data;
		VH->VHNode[node].next = *S;
		*S = node;
	}
}

void pop(VHeap *VH, Stack *S) {
	int temp = *S;
	*S = VH->VHNode[*S].next;
	freeSpace(VH, temp);
}

void insertSorted(VHeap *VH, Stack *S, int data) {
    VHeap tempVH;
    initVHeap(&tempVH);
    Stack temp = -1;
    
    while (*S != -1 && VH->VHNode[*S].elem.data < data) {
        push(&tempVH, &temp, VH->VHNode[*S].elem.data);
        pop(VH, S);
    }
    
    push(VH, S, data);
    
    while (temp != -1) {
        push(VH, S, tempVH.VHNode[temp].elem.data);
        pop(&tempVH, &temp);
    }
}

void printStack(VHeap VH, Stack S) {
	printf("Sorted Stack: ");
    while (S != -1) {
    	printf("%d ", VH.VHNode[S].elem.data);
     	pop(&VH, &S);
    }
}