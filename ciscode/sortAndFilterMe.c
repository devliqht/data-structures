#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX 5

typedef struct
{
  char fname[30];
  char lname[30];
} Name;

typedef struct
{
  Name elems[MAX];
  int front;
  int rear;
} NQueue;

/**************************************/
/*           YOUR TASKS               */
/**************************************/
Name *filterNames(NQueue *nq, char *filterString);
bool insertSorted(NQueue *nq, Name n);

/**************************************/
/*         HELPER FUNCTIONS           */
/**************************************/
void initNQueue(NQueue *nq);
bool isEmpty(NQueue nq);
bool isFull(NQueue nq);
void displayQueue(NQueue nq);
bool enqueue(NQueue *nq, Name n);
bool dequeue(NQueue *nq);
Name front(NQueue nq);


int main() {
    NQueue Q;
    int size;

    initNQueue(&Q);

    printf("Enter size: ");
    scanf("%d", &size);

    for(int i = 0; i < size; i++) {
        Name temp;
        printf("Enter first name: ");
        scanf(" %[^\n]", temp.fname);

        printf("Enter last name: ");
        scanf(" %[^\n]", temp.lname);
        printf("\n");

        if(!insertSorted(&Q, temp)) {
            printf("Queue is FULL!\n\n");
        }
    }

    printf("QUEUE:\n");
    displayQueue(Q);

    char remove[100];
    printf("\nEnter last name to filter from queue: ");
    scanf(" %[^\n]", remove);

    Name *f = filterNames(&Q, remove);

    printf("\nQUEUE:\n");
    displayQueue(Q);

    printf("\nFILTERED NAMES:\n");
    for(int i = 0; strcmp(f[i].lname, "END") != 0; i++) {
        printf("%s %s\n", f[i].fname, f[i].lname);
    }

    return 0;
}

/*Removes the names that matches the filterString to the lastname.
  Returns the removed names. Use the concept of adding a sentinel
  at the end indicating the last item in list as empty strings for
  fname and lname. If there are no names that will match then the
  function should return the sentinel.*/
Name *filterNames(NQueue *nq, char *filterString)
{
	Name* removedNames = (Name*)malloc(sizeof(Name) * (MAX+1)); // we give room for the sentinel value incase all names match
	
	int count = 0;
	if (removedNames != NULL) {
		NQueue temp;
		initNQueue(&temp);
		while (!isEmpty(*nq)) {
			if (strcmp(front(*nq).lname, filterString) == 0) {
				removedNames[count++] = front(*nq);
			}
			enqueue(&temp, front(*nq));
			dequeue(nq);
		}
		while (!isEmpty(temp)) {
			if (strcmp(temp.elems[temp.front].lname, filterString) != 0) {
				enqueue(nq, front(temp));
			}
			dequeue(&temp);
		}
		strcpy(removedNames[count].fname, "END");
		strcpy(removedNames[count].lname, "END");
	}
	
	return removedNames;
}

/*Insert soreted base on lastname. Rember to use the property
  of the queue but without using the functions (enqueue, dequeue, front)*/
bool insertSorted(NQueue *nq, Name n)
{
	NQueue temp;
	temp.front = 1;
	temp.rear = 0;
	bool retval = true;
	if ((nq->rear + 2) % MAX == nq->front) retval = false;
	
	if (retval) {		
	  while ((nq->rear + 1) % MAX != nq->front && strcmp(nq->elems[nq->front].lname, n.lname) > 0) { // if not max
		enqueue(&temp, nq->elems[nq->front]);
		dequeue(nq);
	  }
			
	enqueue(nq, n);
				
	while ((temp.rear + 1) % MAX != temp.front) {
		enqueue(nq, temp.elems[temp.front]);
		dequeue(&temp);
	}	
	}

	return retval;
}


/* Helper Functions */

void initNQueue(NQueue *nq)
{
  nq->front = 1;
  nq->rear = 0;
}

bool isEmpty(NQueue nq)
{
  return (nq.rear + 1) % MAX == nq.front ? true : false;
}

bool isFull(NQueue nq)
{
  return (nq.rear + 2) % MAX == nq.front ? true : false;
}

void displayQueue(NQueue nq)
{
  int stop = (nq.rear + 1) % MAX;

  while (nq.front != stop)
  {
    Name data = front(nq);
    printf("%s %s\n", data.fname, data.lname);

    dequeue(&nq);
    enqueue(&nq, data);
  }
}

bool enqueue(NQueue *nq, Name n)
{
  bool status = false;

  if (!isFull(*nq))
  {
    nq->rear = (nq->rear + 1) % MAX;
    nq->elems[nq->rear] = n;
    status = true;
  }

  return status;
}

bool dequeue(NQueue *nq)
{
  bool status = false;

  if (!isEmpty(*nq))
  {
    nq->front = (nq->front + 1) % MAX;
    status = true;
  }

  return status;
}

Name front(NQueue nq)
{
  Name def = {"XXXX", "XXXXX"};

  return (isEmpty(nq)) ? def : nq.elems[nq.front];
}