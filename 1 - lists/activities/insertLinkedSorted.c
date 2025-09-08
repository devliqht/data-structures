#include <stdlib.h>
#include <stdio.h>

typedef struct node {
	int elem;
	struct node* link;
} *L;

void populateList(L* list) {
	L* trav = list;
	int elems[5] = { 10, 20, 30, 40, 50 };
	for (int i = 0; i < 5; i++) {
		L temp = (L)malloc(sizeof(struct node));
		if (temp != NULL) {
			temp->link = NULL;
			temp->elem = elems[i];
			(*trav) = temp;
			trav = &(*trav)->link;
		}
	}
}

void insertLinkedSorted(L* list, int x) {
	L temp = (L)malloc(sizeof(struct node));
	if (temp != NULL) {
		L* trav;
		for (trav = list; (*trav) != NULL && (*trav)->elem < x; trav = &(*trav)->link) {}
		temp->elem = x;
		temp->link = (*trav);
		(*trav) = temp;
	}
}

void printList(L list) {
	for (; list != NULL; list = list->link) {
		printf("%d -> ", list->elem);
	}
	printf("NULL\n");
}


int main(void) {
	L list = NULL;
	populateList(&list);
	printList(list);
	
	insertLinkedSorted(&list, 25);
	printList(list);
	
	insertLinkedSorted(&list, 5);
	insertLinkedSorted(&list, 55);
	printList(list);
	
	
	return 0;
}