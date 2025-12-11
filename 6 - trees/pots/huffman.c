#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct HuffNode {
	int freq;
	char label;
	struct HuffNode* left, *right;
} HuffNode;

typedef struct {
	HuffNode* arr[MAX];
	int size;
} MinHeap;

void initHeap(MinHeap* heap);
int isLeaf(HuffNode* node);
void insertHuffHeap(MinHeap* heap, char label, int freq);
void insertNode(MinHeap* heap, HuffNode* elem);
HuffNode* buildHuffTree(MinHeap* heap); // this huffman tree already assumes that whatever heap is passed here is already a valid P.O.T with all the frequencies that adds up to 100
HuffNode* extractMinHeap(MinHeap* heap);
void printCodes(HuffNode* root, int arr[], int top);
void printHeap(MinHeap heap);

int main(void) {
	MinHeap heap;
	initHeap(&heap);
	insertHuffHeap(&heap, 'E', 16);
	insertHuffHeap(&heap, 'A', 5);
	insertHuffHeap(&heap, 'C', 12);
	insertHuffHeap(&heap, 'B', 9);
	insertHuffHeap(&heap, 'F', 45);
	insertHuffHeap(&heap, 'D', 13);
	
	printHeap(heap);
	
	printf("Building huffman tree:...\n");
	HuffNode* builtTree = buildHuffTree(&heap);
	printHeap(heap);
	
	int arr[MAX] = {0};
	printCodes(builtTree, arr, 0);
	
	return 0;
}

void initHeap(MinHeap* heap) {
	heap->size = 0;
}

int isLeaf(HuffNode* node) {
	return (node->left || node->right) ? 0 : 1;
}

void insertHuffHeap(MinHeap* heap, char label, int freq) {
	HuffNode* elem = (HuffNode*)malloc(sizeof(struct HuffNode));
	if (elem != NULL) {
		elem->label = label;
		elem->freq = freq;
		elem->left = NULL;
		elem->right = NULL;
		
		insertNode(heap, elem);
	}
}

void insertNode(MinHeap* heap, HuffNode* elem) {
	if (heap->size < MAX) {
	    int curr = heap->size;
	    heap->arr[heap->size++] = elem;
	
	    while (curr != 0 && elem->freq < heap->arr[(curr-1)/2]->freq) {
	        HuffNode* temp = heap->arr[(curr-1)/2];
	        heap->arr[(curr-1)/2] = elem;
	        heap->arr[curr] = temp;
	        curr = (curr-1)/2;
	    }
	}
}

HuffNode* buildHuffTree(MinHeap* heap) {
	HuffNode* tree = (HuffNode*)malloc(sizeof(struct HuffNode));
	if (tree) {
		while (heap->size > 1) { // we can't do heap.size >= 1 cuz we're taking out two elements at a time
			HuffNode* left = extractMinHeap(heap);
			HuffNode* right = extractMinHeap(heap);
			
			HuffNode* merged = (HuffNode*)malloc(sizeof(struct HuffNode));
			if (merged) {
				merged->freq = left->freq + right->freq;
				merged->left = left;
				merged->right = right;
				merged->label = left->label + right->label;
				
				insertNode(heap, merged);
			}
		}
	}
	return extractMinHeap(heap);
}

HuffNode* extractMinHeap(MinHeap* heap) {
	HuffNode* root = heap->arr[0];
	heap->arr[0] = heap->arr[heap->size-1]; // last node
	heap->size--;
	int curr = 0;
	while (curr < heap->size) {
		int smallest = curr;
		int LCidx = 2*curr+1, RCidx = 2*curr+2;
		if (LCidx < heap->size && heap->arr[LCidx]->freq <= heap->arr[curr]->freq) smallest = LCidx;
		if (RCidx < heap->size && heap->arr[RCidx]->freq <= heap->arr[smallest]->freq) smallest = RCidx;
		
		if (smallest != curr) {
			HuffNode* temp = heap->arr[curr];
			heap->arr[curr] = heap->arr[smallest];
			heap->arr[smallest] = temp;
		} else {
			smallest = heap->size + 1;
		}
		curr = smallest;
	}
	
	return root;
}

void printHeap(MinHeap heap) {
	printf("\nMinHeap: \n");
	if (heap.size > 0) {
		for (int i = 0; i < heap.size; i++) {
			printf("[nth: %d, freq: %d, label: %c]\n", i, heap.arr[i]->freq, heap.arr[i]->label);
		}
	} else {
		printf("MinHeap empty!\n");
	}
}


void printCodes(HuffNode* root, int arr[], int top) {
    // Left = 0
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    // Right = 1
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    if (isLeaf(root)) {
        printf("%c: ", root->label);
        for (int i = 0; i < top; ++i) {
            printf("%d", arr[i]);
        }
        printf("\n");
    }
}

