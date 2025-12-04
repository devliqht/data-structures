#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node* prev;
	struct node* link;
} *LIST;

typedef struct {
	LIST front;
	LIST rear;
} LQueue;

int main(void) {
	
}