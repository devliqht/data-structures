#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void BFStrav(BST t);
void initBST(BST* t);
void insertBST(BST* t, int x);
void displayPreorder(BST t);
void displayInorder(BST t);

int main(void) {
	BST tree;
	initBST(&tree);
	insertBST(&tree, 20);
	insertBST(&tree, 16);
	insertBST(&tree, 21);
	insertBST(&tree, 14);
	insertBST(&tree, 18);
	insertBST(&tree, 24);
	insertBST(&tree, 22);
	insertBST(&tree, 5);
	insertBST(&tree, 15);
	insertBST(&tree, 10);
	printf("Preorder: \n");
	displayPreorder(tree);
	printf("\nInorder:\n");
	displayInorder(tree);
	printf("\nBFS:\n");
	BFStrav(tree);
	 
	
	return 0;
}

void initBST(BST* t) {
	(*t) = NULL;
}

void displayPreorder(BST t) {
	if (t != NULL) {
		printf("%d, ", t->elem);
		displayPreorder(t->left);
	 	displayPreorder(t->right);
	}
}

void displayInorder(BST t) {
	if (t != NULL) {
		displayInorder(t->left);
		printf("%d, ", t->elem);
	 	displayInorder(t->right);
	}
}

void insertBST(BST* t, int x) {
	BST* trav = t;
	while ((*trav) != NULL && (*trav)->elem != x) {
		((*trav)->elem < x) ? (trav = &(*trav)->right) : (trav = &(*trav)->left);
	} 
	if ((*trav) == NULL) { // insertion
		BST temp = (BST)malloc(sizeof(struct node));
		temp->elem = x;
		temp->left = NULL;
		temp->right = NULL;
		(*trav) = temp;
	}
}

void BFStrav(BST t) {
	C_Queue q;
	init(&q);
	
	enqueue(&q, t);
	int x = 0;
	while (!isEmpty(q)) {
		printf("Level %d: ", x++);
		
		int stopper = (q.rear + 1) % MAX;
		
		while (q.front != stopper) {
			BST front = dequeue(&q);
			printf("%d, ", front->elem);
			if (front->left != NULL) enqueue(&q, front->left);
			if (front->right != NULL) enqueue(&q, front->right);
		}
		printf("\n");
	}
}

BST getMin(BST t) {
    BST current = t;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}