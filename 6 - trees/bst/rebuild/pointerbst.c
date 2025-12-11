#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int elem;
	struct node* left;
	struct node* right;
} *BST;

void insertBST(BST* t, int member);
void preorderBST(BST t);
void postorderBST(BST t);
void deleteBST(BST* t, int member);
int locateMember(BST t, int member);
BST maxBST(BST t);
BST minBST(BST t);

int main(void) {
	BST t = NULL;
	insertBST(&t, 50);
	insertBST(&t, 35);
	insertBST(&t, 25);
	insertBST(&t, 15);
	insertBST(&t, 30);
	insertBST(&t, 55);
	insertBST(&t, 75);
	insertBST(&t, 40);
	insertBST(&t, 60);
	
	preorderBST(t);
	printf("\n");
	postorderBST(t);
	deleteBST(&t, 35);
	printf("\n");
	preorderBST(t);
	return 0;
}

void insertBST(BST* t, int member) {
	BST* trav = t;
	while ((*trav) != NULL) {
		(member < (*trav)->elem) ? (trav = &(*trav)->left) : (trav = &(*trav)->right);
	}
	BST temp = (BST)malloc(sizeof(struct node));
	if (temp != NULL) {
		temp->elem = member;
		temp->left = NULL;
		temp->right = NULL;
		(*trav) = temp;
	}
}

void preorderBST(BST t) {
	if (t != NULL) {
		printf("%d, ", t->elem);
		preorderBST(t->left);
		preorderBST(t->right);
	}
}

void postorderBST(BST t) {
	if (t != NULL) {
		postorderBST(t->left);
		postorderBST(t->right);
		printf("%d, ", t->elem);
	}
}

void deleteBST(BST* t, int member) {
	BST* trav = t;	
	while ((*trav) != NULL && (*trav)->elem != member) {
		(member < (*trav)->elem) ? (trav = &(*trav)->left) : (trav = &(*trav)->right);
	}
	if (*trav != NULL) {
		// Case three first: it has both left and right children
		if ((*trav)->left != NULL && (*trav)->right != NULL) {
			BST successor = minBST((*trav)->right);
		 	(*trav)->elem = successor->elem;
			deleteBST(&(*trav)->right, successor->elem);
		} else {
			BST temp = (*trav);
			BST successor = ((*trav)->left == NULL) ? (*trav)->right : (*trav)->left; // This is case one and two combined. If both are NULL (leaf), still works.
			(*trav) = successor;
			free(temp);
		}
	}
}

BST minBST(BST t) {
	while (t->left != NULL) {
		t = t->left;
	}
	return t;
}

BST maxBST(BST t) {
	while (t->right != NULL) {
		t = t->right;
	}
	return t;
}

