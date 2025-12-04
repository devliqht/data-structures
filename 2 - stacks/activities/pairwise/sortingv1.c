#include "headers/StacksArr.h"
#include <limits.h>

Stack sortStack(Stack S) {
	Stack ordered;
	Stack tempStack;
	
	init(&ordered);
	init(&tempStack);
	
	while (!isFull(ordered)) {
		int max = INT_MIN;
		int maxCount = 0;
		while (!isEmpty(S)) {
			int temp = top(&S);
			pop(&S);
			if (temp > max) {
				max = temp;
				maxCount = 1;
			} else if (temp == max) {
				maxCount++; // for duplicates
			}
			push(&tempStack, temp);
		}
		while(!isEmpty(tempStack)) {
			if (top(&tempStack) != max) {
				push(&S, top(&tempStack));
			}
			pop(&tempStack);
		}

		for (int idx = 0; idx < maxCount; idx++) push(&ordered, max);
	}
	return ordered;
}

int main(void) {
	Stack S = { {9, 12, 1, 16, 15, 11, 4, 6, 5, 1 }, 9 }; // 10 elements, top is at index 9
	Stack ordered = sortStack(S);
	printStack(&ordered);

	return 0;
}
