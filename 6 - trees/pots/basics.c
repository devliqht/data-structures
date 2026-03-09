#include <stdio.h>
#include <stdlib.h>
#include "basics.h"

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
	// Insert min heap function:
	// Insert the element at the end of the heap, then bubble up.
	int curr = 0;
	if (heap->size < MAX) { // If it is a valid element, then	
		curr = heap->size; // Set curr to the last index.
		heap->array[heap->size++] = i; // Insert the element into the last index.
	}
	while (curr != 0 && heap->array[curr] < getParentElement(*heap, curr)) {
		// While curr is not 0 (root) AND curr is less than parent element, we bubble up
		// by swapping the current element with the parent.
		// This satisfies the property of P.O.Ts wherein each children must be LESS THAN its parent.
		int temp = getParentElement(*heap, curr);
		heap->array[getParentIndex(curr)] = heap->array[curr];
		heap->array[curr] = temp;
		// We set curr to the parent index, ready to bubble up if the parent of this node is bigger than our inserted element.
		curr = getParentIndex(curr);
	}
	printf("Inserted %d successfully.\n", i);
}

int extractMin(MinHeap* heap) {
	// We get the root element first.
	int rootElem = heap->array[0];
	// After getting the root element, we then replace it with the last node of the partially ordered tree.
	heap->array[0] = heap->array[heap->size - 1];
	// Decrease the size after swapping.
	heap->size--;
	int curr = 0; 
	while (curr < heap->size) {
		// We do a loop for the entire P.O.T, checking if its left child or right child is correct.
		int LCIdx = getLCIndex(curr), RCIdx = getRCIndex(curr), smallest = curr;
		// If left child is smaller, the smallest is left child.
		if (LCIdx < heap->size && heap->array[LCIdx] <= heap->array[curr]) smallest = LCIdx;
		// Since if the above statement were to be true, we compare it to the right child if the right child is smaller. If it is, right child is smaller. Otherwise smallest would remain with the left child.
		if (RCIdx < heap->size && heap->array[RCIdx] <= heap->array[smallest]) smallest = RCIdx;
		
		// If the smallest was still curr, we set curr to be an out-of-bounds index, effectively ending the loop, because curr (heap->size + 1) > heap->size.
		if (smallest == curr) {
			smallest = heap->size + 1;  
		} else { // Else, we swap the elements.
			int temp = heap->array[curr];
			heap->array[curr] = heap->array[smallest];
			heap->array[smallest] = temp;
		}
		// We set curr to be the index of our new smallest element. This will trigger the loop to execute again, since this would be less than heap->size.
		curr = smallest;
	}
	return rootElem; // the min
}