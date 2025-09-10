#ifndef STACK_LL_H
#define STACK_LL_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char elem;
	struct node* link;
} *LIST;

typedef struct {
	LIST top;
} Stack;

void init(Stack* S) {
	S->top = NULL;
}

int isEmpty(Stack S) {
	return (S.top == NULL) ? 1 : 0;
}

int isFull(Stack S) {
	return 0; // since it's a linkedlist?
}

void push(Stack* S, char elem) {
	LIST temp = (LIST)malloc(sizeof(struct node));
	if (temp != NULL) {
		temp->elem = elem;
		temp->link = S->top;
		S->top = temp;
	}
}

void pop(Stack* S) {
	if (!isEmpty(*S)) {
		LIST temp = S->top;
		S->top = temp->link;
		free(temp);
	}
}

char top(Stack* S) {
	return (!isEmpty(*S)) ? S->top->elem : '\0'; // or any sentinel value here
}

void printStack(Stack* S) {
	printf("\nSTACK: \n");
	if (!isEmpty(*S)) {
		// To traverse a stack without ->link traversal , we basically
		// create a new Stack temp, traverse the Stack* S by viewing
		// the top, reading the data, push it to the temp, then pop it
		Stack temp;
		init(&temp);
		
		while (!isEmpty(*S)) {
			// We read the top elem data first, then push it, to the temp,
			// then pop.
			printf("%c\n", top(S));
			push(&temp, top(S));
			pop(S);
		}
		while (!isEmpty(temp)) {
			// We push back to the original Stack the elements of temp
			// Basically like nothing happened
			push(S, top(&temp));
			pop(&temp);
		}
	}
}

#endif