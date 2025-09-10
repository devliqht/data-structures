#include <stdio.h>
#include <stdlib.h>


typedef struct node {
	char elem;
	struct node* link;
} *LIST;

void printList(LIST L);
void insertFirst(LIST* L, char elem);
void insertLast(LIST* L, char elem);
void insertAt(LIST* L, char elem, int pos);

void deleteFirst(LIST* L);
void deleteLast(LIST* L);
void deleteElem(LIST* L, char elem);

void member(LIST L, char elem);


int main(void) {
	LIST L = NULL;
	
	insertFirst(&L, 'u');
	insertFirst(&L, 's');
	insertFirst(&L, 'c');
	printList(L);
	insertLast(&L, 't');
	insertLast(&L, 'c');
	printList(L);
	insertAt(&L, 'n', 1);
	printList(L);
	insertAt(&L, 'i', 2);
	printList(L);
	insertAt(&L, 'w', 0);
	printList(L);
	deleteFirst(&L);
	printList(L);
	
	
	return 0;
	
}

void printList(LIST L) {
	for (;L!=NULL;L=L->link){
		printf("%c %s", L->elem, (L->link!=NULL) ? "-> " : "\n");
	}
}

void insertFirst(LIST* L, char elem) {
	LIST temp = (LIST)malloc(sizeof(struct node));
	if (temp != NULL) {
		temp->elem = elem;
		temp->link = (*L);
		(*L) = temp;
	}
}

void insertLast(LIST* L, char elem) {
	LIST* trav;
	for (trav = L; (*trav) != NULL; trav = &(*trav)->link){}
	LIST temp = (LIST)malloc(sizeof(struct node));
	if (temp != NULL) {
		temp->elem = elem;
		temp->link = NULL;
		(*trav) = temp;
	}
}

void insertAt(LIST* L, char elem, int pos) {
	LIST* trav;
	int idx = 0;
	for (trav = L; (*trav) != NULL && idx < pos ; trav = &(*trav)->link, ++idx){}
	
	LIST temp = (LIST)malloc(sizeof(struct node));
	if (temp != NULL) {
		temp->elem = elem;
		temp->link = (*trav);
		(*trav) = temp;
	}
}

void deleteFirst(LIST* L) {
	LIST temp = (*L);
	(*L) = temp->link;
	free(temp);
}