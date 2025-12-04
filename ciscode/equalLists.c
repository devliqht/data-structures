#include <stdio.h>
#include <stdlib.h>

typedef enum {
    TRUE,
    FALSE
} boolean;

typedef struct node {
    int data;
    struct node *next;
} *List;

/*************************************/
/*           YOUR TASKS              */
/*************************************/
boolean isEqualNotSorted(List A, List B);
boolean isEqualSorted(List A, List B);
void sort(List L);


/*************************************/
/*       PROVIDED FUNCTIONS          */
/*************************************/
void initList(List *L);
void insertFirst(List *L, int data);
void deleteFirst(List *L);
void populate(List *L, int size);
void printList(List L);
void freeAll(List *L);

int main() {
    List A, B;
    int sizeA, sizeB;

    initList(&A);
    initList(&B);

    printf("Enter size of List A: ");
    scanf("%d", &sizeA);
    populate(&A, sizeA);

    printf("\nEnter size of List B: ");
    scanf("%d", &sizeB);
    populate(&B, sizeB);

    printf("\nBefore Sorting:\n");
    printf("List A: ");
    printList(A);
    printf("List B: ");
    printList(B);

    printf("NOT SORTED: %s\n", (isEqualNotSorted(A, B) == TRUE) ? "EQUAL" : "NOT EQUAL");

    sort(A);
    sort(B);

    printf("\nAfter Sorting:\n");
    printf("List A: ");
    printList(A);
    printf("List B: ");
    printList(B);

    printf("SORTED: %s", (isEqualSorted(A, B) == TRUE) ? "EQUAL" : "NOT EQUAL");

    freeAll(&A);
    freeAll(&B);

    return 0;
}

boolean isEqualNotSorted(List A, List B) {
    // THIS APPROACH ASSUMES THAT ALL NUMBERS ARE NON NEGATIVE
	int idx = 0;
	List aTrav, bTrav;
	for (aTrav = A, bTrav=B; aTrav != NULL && bTrav != NULL; aTrav = aTrav->next, bTrav = bTrav->next) {}
	if (aTrav == bTrav) { // check if both null, if not, the lists dont have same size
		int hash[100] = {0}; // arbitrary number. not max for simplicity
		for (aTrav = A; aTrav != NULL; aTrav = aTrav->next) {
			hash[aTrav->data]++;
		}
		for (bTrav = B; bTrav != NULL; bTrav = bTrav->next) {
			hash[bTrav->data]--;
		}
		for (; idx < 100 && hash[idx] == 0; idx++){} // at any case it's not, it's not equal
	}
	return (idx == 100) ? TRUE : FALSE; // arbitrary number
}


boolean isEqualSorted(List A, List B) {
    List aTrav, bTrav;
    for (aTrav = A, bTrav = B; (aTrav != NULL && bTrav != NULL) && (aTrav->data == bTrav->data); aTrav = aTrav->next, bTrav = bTrav->next) {}
    return (aTrav == NULL && bTrav == NULL) ? TRUE : FALSE;
}

void sort(List L) {
    int swapped = 1;
    List trav;
    if (L == NULL || L->next == NULL) return;
    while (swapped) {
        swapped = 0;
        for (trav = L; trav->next != NULL; trav = trav->next) {
            if (trav->data > trav->next->data) {
                int temp = trav->data;
                trav->data = trav->next->data;
                trav->next->data = temp;
                swapped = 1;
            }
        }
    }
}

void initList(List *L) {
    *L = NULL;
}

void insertFirst(List *L, int data) {
    List temp = (List)malloc(sizeof(struct node));
    
    if(temp != NULL) {
        temp->data = data;
        temp->next = *L;
        *L = temp;
    }
}

void deleteFirst(List *L) {
    if(*L != NULL) {
        List temp = *L;
        *L = temp->next;
        free(temp);
    }
}

void populate(List *L, int size) {
    for(int i = 0; i < size; i++) {
        int temp;
        printf("Enter number %d: ", i + 1);
        scanf("%d", &temp);
        insertFirst(L, temp);
    }
}

void printList(List L) {
    if(L == NULL) {
        printf("EMPTY");
    }

    for(List curr = L; curr != NULL; curr = curr->next) {
        printf("%d ", curr->data);
    }

    printf("\n");
}

void freeAll(List *L) {
    List del;

    while(*L != NULL) {
        del = *L;
        *L = (*L)->next;
        free(del);
    }
}