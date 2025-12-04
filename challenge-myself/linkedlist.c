#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char FName[24];
	char LName[16];
	char MI;
	int age;
} StudType;

typedef struct node {
	struct node* link;
	StudType stud;
} *StudList;

void initList(StudList *L);
void printList(StudList L);

void insertFirstStudent(StudList *L, StudType stud);
void insertLastStudent(StudList *L, StudType stud);
void deleteStudent(StudList *L, StudType stud);
void deleteStudentIfAge(StudList *L, int age);

int main(void) {
	StudList L;
	initList(&L);
	StudType matt = { "Matt Erron", "Cabarrubias", 'G', 20 };
	StudType elisa = { "Elisa Pamela Marie", "Magno", 'H', 19 };
	StudType matthew = { "Matthew Angelo", "Lumayno", 'G', 19 };
	insertFirstStudent(&L, matt);
	insertLastStudent(&L, elisa);
	insertLastStudent(&L, matthew);
	printList(L);
	
	deleteStudent(&L, matthew);
	printList(L);
	return 0;
}

void initList(StudList *L) {
	*L = NULL;
}

void printList(StudList L) {
	printf("\nSTUDENT LIST:\n");
	
	int idx = 1;
	for (;L != NULL; L = L->link) {
		printf("\nSTUDENT #%d:\n", idx++);
		printf("STUDENT NAME: %s\n", L->stud.FName);
		printf("STUDENT LAST NAME: %s\n", L->stud.LName);
		printf("STUDENT MI: %c\n", L->stud.MI);
		printf("STUDENT AGE: %d\n", L->stud.age);
	}
}

void insertFirstStudent(StudList *L, StudType stud) {
	StudList Ltemp = (StudList)malloc(sizeof(struct node));
	if (Ltemp != NULL) {
		Ltemp->link = *L;
		Ltemp->stud = stud;
		*L = Ltemp;
		printf("Successfully inserted student to the first of the list!");
	}
}

void insertLastStudent(StudList *L, StudType stud) {
	StudList Ltemp = (StudList)malloc(sizeof(struct node));
	if (Ltemp != NULL) {
		StudList* trav;
		for (trav = L; (*trav) != NULL; trav = &(*trav)->link) {};
		Ltemp->stud = stud;
		Ltemp->link = NULL;
		(*trav) = Ltemp;
	}
	printf("Successfully inserted student to the end of the list!\n");
}

void deleteStudent(StudList *L, StudType stud) {
	StudList *trav;
	for (trav = L; (*trav) != NULL && strcmp(stud.LName, (*L)->stud.LName) != 0; trav = &(*trav)->link) {}
	if (*trav != NULL) {
		StudList temp = *trav;
		(*trav) = (*trav)->link;
		free(temp);
		printf("Found student and deleted!\n");
	}
}