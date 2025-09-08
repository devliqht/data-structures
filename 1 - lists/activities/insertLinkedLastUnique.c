#include <stdlib.h>
#include <stdio.h>

typedef struct node {
	char elem;
	struct node* link;
} *L;

void populateList(L* list) {
	L* trav = list;
	char elems[5] = { 'u', 's', 'c', 't', 'c' };
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

void insertLastUnique(L* list, char x) {
	L* trav;
	for (trav = list; (*trav) != NULL && (*trav)->elem != x; trav = &(*trav)->link) {}
	if ((*trav) == NULL) {
		L temp = (L)malloc(sizeof(struct node));
		if (temp != NULL) {
			temp->elem = x;
			temp->link = NULL; // we're appending at the end of the list. We can do temp->link = (*trav) but = NULL is clearer.
			(*trav) = temp;
		}
	}
}

void printList(L list) {
	for (; list != NULL; list = list->link) {
		printf("%c -> ", list->elem);
	}
	printf("NULL\n");
}

int main(void) {
	L list = NULL;
	populateList(&list);
	printList(list);
	
	insertLastUnique(&list, 'f');
	printList(list);
	
	return 0;	
}