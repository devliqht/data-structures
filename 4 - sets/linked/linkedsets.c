#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node* link;
} nodeType, *SET;

void initList(SET* L) {
	(*L) = NULL;
}

void populateList(SET* L, int option) {
	int caseOne[10] = {1, 3, 5, 7, 9, 10, 11, 12, 13, 14};
	int caseTwo[10] = {2, 4, 5, 6, 8, 10, 12, 14, 16, 18};

	if (option) {
		for (int idx = 0; idx < 10; idx++) {
			SET temp = (SET)malloc(sizeof(nodeType));
			if (temp != NULL) {
				SET* trav;
				for (trav = L; (*trav) != NULL; trav = &(*trav)->link){}
				temp->data = caseOne[idx];
				temp->link = NULL;
				(*trav) = temp;
			}
		}
	} else {
		for (int idx = 0; idx < 10; idx++) {
			SET temp = (SET)malloc(sizeof(nodeType));
			if (temp != NULL) {
				SET* trav;
				for (trav = L; (*trav) != NULL; trav = &(*trav)->link){}
				temp->data = caseTwo[idx];
				temp->link = NULL;
				(*trav) = temp;
			}
		}
	}
}

void printList(SET L) {
	printf("\nSET:\n{ ");
	for (; L != NULL; L=L->link) {
		printf("%d%s", L->data, (L->link != NULL) ? ", " : " }\n");
	}
}

SET Union(SET A, SET B) {
	SET C = NULL;
	SET *cPtr = &C;
	while (A != NULL && B != NULL) {
		(*cPtr) = (SET)malloc(sizeof(nodeType));
		if ((*cPtr) != NULL) {
			if (A->data < B->data) {
				(*cPtr)->data = A->data;
				A = A->link;
			} else {
				if (A->data == B->data) {
					(*cPtr)->data = A->data;
					A = A->link;
				} else {
					(*cPtr)->data = B->data;
				}
				B = B->link; // We move B regardless if it's equal or not. 
			}
			cPtr = &(*cPtr)->link; // At every iteration of the loop, we're always guaranteed to store an element. 
		}
	}
	
	SET dPtr = (A != NULL) ? A : B;
	while (dPtr != NULL) {
		(*cPtr) = (SET)malloc(sizeof(nodeType));
		if ((*cPtr) != NULL) {
			(*cPtr)->data = dPtr->data;
			cPtr = &(*cPtr)->link;
		}
		dPtr = dPtr->link;
	}
	
	(*cPtr) = NULL;
	return C;
}

int main(void) {
	SET A;
	initList(&A);
	SET B;
	initList(&B);
	populateList(&A, 1);
	populateList(&B, 0);

	printList(A);
	printList(B);
	
	SET C = Union(A, B);
	printList(C);
	return 0;
}
