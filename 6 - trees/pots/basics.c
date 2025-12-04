#include <stdio.h>
#include <stdlib.h>
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

int main(void) {
	MinHeap heap = { {3, 5, 7, 7, 6, 8, 9}, 7 };
	
	printf("The index of the left child of Node %d is %d, which is element %d.", 2, getLCIndex(2), getLCElement(heap, 2));
	insertMinHeap(&heap, 2);
	printf("The heap now is: ");
	for (int i = 0; i < heap.size; i++) {
		printf("%d ", heap.array[i]);
	}
	printf("Extracting min: %d\n", extractMin(&heap));
	printf("The heap now is: ");
	for (int i = 0; i < heap.size; i++) {
		printf("%d ", heap.array[i]);
	}
	
	printf("Extracting min: %d\n", extractMin(&heap));
	printf("The heap now is: ");
	for (int i = 0; i < heap.size; i++) {
		printf("%d ", heap.array[i]);
	}
	return 0;
}

Node getLCIndex(Node i) {
	return 2*i+1;
}

Node getRCIndex(Node i) {
	return 2*i+2;
}

Node getParentIndex(Node i) {
	return (i-1)/2;
}

Node getLCElement(MinHeap heap, Node i) {
	return heap.array[getLCIndex(i)];
}

Node getRCElement(MinHeap heap, Node i) {
	return heap.array[getRCIndex(i)];
}

Node getParentElement(MinHeap heap, Node i) {
	return heap.array[getParentIndex(i)];
}

void insertMinHeap(MinHeap* heap, Node i) {
	int curr;
	if (heap->size < MAX) {
		curr = heap->size;
		heap->array[heap->size++] = i;
	}
	while (curr != 0 && heap->array[curr] < getParentElement(*heap, curr)) {
		int temp = getParentElement(*heap, curr);
		heap->array[getParentIndex(curr)] = heap->array[curr];
		heap->array[curr] = temp;
		curr = getParentIndex(curr);
	}
	printf("Inserted %d successfully.\n", i);
}

int extractMin(MinHeap* heap) {
	int rootElem = heap->array[0];
	heap->array[0] = heap->array[heap->size - 1];
	heap->size--;
	int curr = 0; 
	while (curr < heap->size) {
		int LCIdx = getLCIndex(curr), RCIdx = getRCIndex(curr), smallest = curr;
		if (LCIdx < heap->size && heap->array[LCIdx] <= heap->array[curr]) smallest = LCIdx;
		if (RCIdx < heap->size && heap->array[RCIdx] <= heap->array[smallest]) smallest = RCIdx;
		
		if (smallest == curr) {
			smallest = heap->size + 1; // set it to an invalid pos to break the loop without break;
		} else {
			int temp = heap->array[curr];
			heap->array[curr] = heap->array[smallest];
			heap->array[smallest] = temp;
		}
		curr = smallest;
	}
	return rootElem; // the min
}