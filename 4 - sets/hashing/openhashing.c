#include <stdio.h>
#include <stdlib.h>
#define MAX 10
typedef struct node {
	int data;
	struct node* link;
} *LIST;

typedef LIST Dictionary[MAX];

void initDict(Dictionary D);
void displayDict(Dictionary D);
int hash(int elem);
void insertDict(Dictionary D, int elem);
void deleteDict(Dictionary D, int elem);
void insertSorted(Dictionary D, int elem);
void insertUnique(Dictionary D, int elem);

int main(void) {
	
	Dictionary dict;
	initDict(dict);
	insertDict(dict, 10);

	insertDict(dict, 20);
	insertDict(dict, 9);
	insertDict(dict, 8);
	insertDict(dict, 78);

	displayDict(dict);
	deleteDict(dict, 78);
	deleteDict(dict, 25);
	
	displayDict(dict);
	insertDict(dict, 30);
	insertDict(dict, 40);
	insertSorted(dict, 25);
	insertSorted(dict, 65);
	insertSorted(dict, 45);
	insertSorted(dict, 55);
	insertSorted(dict, 35);
	
	displayDict(dict);
	insertUnique(dict, 75);
	insertUnique(dict, 75);
	displayDict(dict);
	
	
	return 0;
	
}

void displayDict(Dictionary D) {
	for (int idx = 0; idx < MAX; idx++) {
		printf("%d: ", idx);
		LIST* trav = &D[idx];
		while ((*trav) != NULL) {
			printf("%d%s", (*trav)->data, ((*trav)->link == NULL) ? " " : " -> ");
			trav = &(*trav)->link;
		}
		printf("\n");
	}
}

void initDict(Dictionary D) {
	for (int idx = 0; idx < MAX; idx++) D[idx] = NULL;
}

int hash(int elem) {
	return (elem % MAX);
}

void insertDict(Dictionary D, int elem) {
	int elemIdx = hash(elem);
	LIST temp = (LIST)malloc(sizeof(struct node));
	if (temp != NULL) {
		temp->data = elem;
		temp->link = D[elemIdx];
		D[elemIdx] = temp;
		printf("Inserted %d to the dictionary.\n", elem);
	}
}

void deleteDict(Dictionary D, int elem) {
	int elemIdx = hash(elem);
	LIST* trav;
	for (trav = &D[elemIdx]; (*trav) != NULL && (*trav)->data != elem; trav = &(*trav)->link){};
	if (*trav != NULL) {
		LIST temp = (*trav);
		(*trav) = temp->link;
		free(temp);
		printf("Deleted %d from the dictionary.\n", elem);
	} else {
		printf("Could not find %d in the dictionary.\n", elem);
	}
}

void insertSorted(Dictionary D, int elem) {
	int elemIdx = hash(elem);
	LIST* trav;
	for (trav = &D[elemIdx]; (*trav) != NULL && (*trav)->data < elem; trav = &(*trav)->link){};
	LIST temp = (LIST)malloc(sizeof(struct node));
	if (temp != NULL) {
		temp->data = elem;
		temp->link = (*trav);
		(*trav) = temp;
		printf("Inserted sorted %d to the dictionary.\n", elem);
	}
}

void insertUnique(Dictionary D, int elem) {
	int elemIdx = hash(elem);
	LIST* trav;
	for (trav = &D[elemIdx]; (*trav) != NULL && (*trav)->data != elem; trav = &(*trav)->link){};
	if ((*trav) == NULL) {
		LIST temp = (LIST)malloc(sizeof(struct node));
		if (temp != NULL) {
			temp->data = elem;
			temp->link = (*trav);
			(*trav) = temp;
			printf("Uniquely inserted %d to the dictionary.\n", elem);
		}
	} else {
		printf("Element %d already exists in the dictionary.\n", elem);
	}
}