#ifndef POTS_BASICS
#define POTS_BASICS
#define MAX 10

typedef struct {
    int array[MAX];
    int size;
} MinHeap;

typedef int Node;

Node getLCIndex(Node i);
Node getLCElement(MinHeap heap, Node i);
Node getRCIndex(Node i);
Node getRCElement(MinHeap heap, Node i);
Node getParentIndex(Node i);
Node getParentElement(MinHeap heap, Node i);
void insertMinHeap(MinHeap* heap, Node i);
int extractMin(MinHeap* heap);

#endif