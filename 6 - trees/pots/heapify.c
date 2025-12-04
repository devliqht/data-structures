#include <stdio.h> // Included for potential testing

// Pre-defined structure for the minHeap
#define MAX 15
typedef struct {
    int elem[MAX];
    int lastNdx;
} minHeap;

void display(int [], int);
void heapifySubtree(minHeap *H, int subroot);

int main(void) {
	minHeap heapArea = {{ 6, 10, 5, 10, 2, 9, 7, 18, 4, 9, 3 }, 11};
	display(heapArea.elem, heapArea.lastNdx);
	heapifySubtree(&heapArea, 4); // Node Value 2
	display(heapArea.elem, heapArea.lastNdx);
	heapifySubtree(&heapArea, 3); // Node value 10
	display(heapArea.elem, heapArea.lastNdx);
	heapifySubtree(&heapArea, 2); // Node value 5
	display(heapArea.elem, heapArea.lastNdx);
	heapifySubtree(&heapArea, 1); // Node value 10
	display(heapArea.elem, heapArea.lastNdx);
	
	

	return 0;
}

void display(int arr[], int lastndx) {
	for (int i = 0; i < lastndx; i++) printf("%d ", arr[i]);
	printf("\n");
}
/**
 * @brief Restores the min-heap property for a subtree.
 * @details This function assumes that the subtrees of the given root are already min-heaps.
 * It "sifts down" the root element to its correct position to maintain the
 * min-heap property, where a parent node is always less than or equal to its children.
 * @param H Pointer to the minHeap structure.
 * @param subRootNdx The index of the root of the subtree to heapify.
 */
 void heapifySubtree(minHeap *H, int subroot) {
     int currentNdx = subroot, smallest;
     
     while (2 * currentNdx + 1 <= H->lastNdx) {
         int LC = 2 * currentNdx + 1, RC = 2 * currentNdx + 2;
         smallest = (LC <= H->lastNdx && H->elem[LC] < H->elem[currentNdx]) ? LC : currentNdx;
         
         if (RC <= H->lastNdx && H->elem[RC] < H->elem[smallest]) smallest = RC;
         
         if (smallest == currentNdx) {
             currentNdx = H->lastNdx + 1;
         } else {
             int temp = H->elem[currentNdx];
             H->elem[currentNdx] = H->elem[smallest];
             H->elem[smallest] = temp;
             currentNdx = smallest;
         }
     }
 }

