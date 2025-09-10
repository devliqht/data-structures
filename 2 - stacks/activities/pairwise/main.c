#include "headers/StacksLinked.h"
// #include "headers/StacksArr.h"

int main(void) {

	Stack S;
	init(&S);
	push(&S, 'u');
	push(&S, 's');
	push(&S, 'c');
	push(&S, 't');
	push(&S, 'c');
	printStack(&S);
	printf("TOP ELEMENT: %c\n", top(&S));
	pop(&S);
	printStack(&S);
	printf("TOP ELEMENT: %c\n", top(&S));
	
	return 0;
}