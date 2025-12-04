#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int elem;
	struct node* left;
	struct node* right;
} *BST;

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
	displayPreorder(tree);
	printf("\n");
	displayInorder(tree);
	
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
	} // This is pointer to pointer to node approach. We start at the root, check if x is bigger than the element (first is the root)
	// If it is, then we go to the right. If not, we go to the left.
	if ((*trav) == NULL) { // insertion
		BST temp = (BST)malloc(sizeof(struct node));
		temp->elem = x;
		temp->left = NULL;
		temp->right = NULL;
		(*trav) = temp;
	}
}