#ifndef STACKS_ARR_H
#define STACKS_ARR_H

#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct {
	int Elem[MAX];
	int top;
} Stack;

void init(Stack* S) {
	S->top = -1;
}

int isEmpty(Stack S) {
	return (S.top == -1) ? 1 : 0;
}

int isFull(Stack S) {
	return (S.top == MAX-1) ? 1 : 0;
}

void push(Stack* S, char elem) {
	if (!isFull(*S)) S->Elem[++S->top] = elem;
}

char pop(Stack* S) {
	return (!isEmpty(*S)) ? S->Elem[S->top--] : -1;
}
  
char top(Stack* S) {
	return (!isEmpty(*S)) ? S->Elem[S->top] : -1;
}

void printStack(Stack* S) {
	printf("\nSTACK: \n");
	Stack temp;
	init(&temp);
	while (!isEmpty(*S)) {
		printf("%d\n", top(S));
		push(&temp, top(S));
		pop(S);
	}
	while (!isEmpty(temp)) {
		push(S, top(&temp)); 
		pop(&temp);
	}
}


#endif