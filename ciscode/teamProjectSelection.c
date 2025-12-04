#include <stdio.h>
#include <stdlib.h>
#define MAX 5

typedef int SET[MAX];

// Function prototypes
SET* Union(SET A, SET B);
SET* Intersection(SET A, SET B);
SET* Difference(SET A, SET B);
void displaySet(SET S);
void assignSet(SET target, int values[MAX]);

SET* FindApprovedTools(SET Design, SET Programming, SET Marketing);

int main() {
  int testCase;
  SET Design;
  SET Programming;
  SET Marketing;

  printf("Select a project scenario to simulate (1-10): ");
  scanf("%d", &testCase);

  int d[MAX], p[MAX], m[MAX];

  switch (testCase) {
      case 1:
          assignSet(d, (int[]){1, 1, 0, 0, 1});
          assignSet(p, (int[]){0, 0, 1, 0, 1});
          assignSet(m, (int[]){1, 0, 0, 1, 1});
          break;
      case 2:
          assignSet(d, (int[]){1, 1, 1, 1, 1});
          assignSet(p, (int[]){1, 1, 1, 1, 1});
          assignSet(m, (int[]){1, 1, 1, 1, 1});
          break;
      case 3:
          assignSet(d, (int[]){0, 0, 0, 0, 0});
          assignSet(p, (int[]){1, 1, 1, 1, 1});
          assignSet(m, (int[]){0, 0, 0, 0, 0});
          break;
      case 4:
          assignSet(d, (int[]){0, 0, 0, 0, 0});
          assignSet(p, (int[]){0, 0, 0, 0, 0});
          assignSet(m, (int[]){1, 1, 1, 1, 1});
          break;
      case 5:
          assignSet(d, (int[]){1, 1, 0, 0, 0});
          assignSet(p, (int[]){0, 0, 1, 0, 1});
          assignSet(m, (int[]){1, 0, 0, 1, 0});
          break;
      case 6:
          assignSet(d, (int[]){1, 0, 1, 0, 1});
          assignSet(p, (int[]){0, 1, 0, 1, 0});
          assignSet(m, (int[]){1, 1, 1, 1, 1});
          break;
      case 7:
          assignSet(d, (int[]){0, 1, 0, 1, 0});
          assignSet(p, (int[]){0, 0, 0, 0, 0});
          assignSet(m, (int[]){1, 1, 1, 1, 1});
          break;
      case 8:
          assignSet(d, (int[]){1, 1, 0, 1, 0});
          assignSet(p, (int[]){1, 0, 1, 0, 1});
          assignSet(m, (int[]){0, 1, 0, 1, 0});
          break;
      case 9:
          assignSet(d, (int[]){1, 0, 0, 0, 0});
          assignSet(p, (int[]){0, 1, 0, 0, 0});
          assignSet(m, (int[]){0, 0, 1, 0, 0});
          break;
      case 10:
          assignSet(d, (int[]){0, 0, 0, 0, 0});
          assignSet(p, (int[]){0, 0, 0, 0, 0});
          assignSet(m, (int[]){0, 0, 0, 0, 0});
          break;
      default:
          printf("Invalid test case.\n");
          return 1;
  }

  assignSet(Design, d);
  assignSet(Programming, p);
  assignSet(Marketing, m);
  
  // SET* Approved = FindApprovedTools(Design, Programming, Marketing);

  // displaySet(*Approved);

  // free(Approved);
  return 0;
}

// TODO: Implement this function
SET* FindApprovedTools(SET Design, SET Programming, SET Marketing) {
	return Union(*(Intersection(Design, Marketing)), Programming);
}

// ====== SET OPERATION IMPLEMENTATIONS ======
SET* Union(SET A, SET B) {
	SET* temp = (SET*)malloc(sizeof(SET));
	if (temp != NULL) {
		for (int idx = 0; idx < MAX; idx++) {
			(*temp)[idx] = A[idx] | B[idx];
		}
	}
	return temp;
}

SET* Intersection(SET A, SET B) {
	SET* temp = (SET*)malloc(sizeof(SET));
	if (temp != NULL) {
		for (int idx = 0; idx < MAX; idx++) {
			(*temp)[idx] = A[idx] & B[idx];
		}
	}
	return temp;
  
}

SET* Difference(SET A, SET B) {
	SET* temp = (SET*)malloc(sizeof(SET));
	if (temp != NULL) {
		for (int idx = 0; idx < MAX; idx++) {
			(*temp)[idx] = A[idx] & !B[idx];
		}
	}
	return temp;
}

void displaySet(SET S) {
  printf("\nApproved Tools for the Project:\n");
  printf("(1 = approved, 0 = not approved)\n");
  for (int i = 0; i < MAX; i++) {
      printf("%d ", S[i]);
  }
  
  const char* tools[MAX] = {"Canva", "Figma", "GitHub", "Trello", "ChatGPT"};
  printf("\n\n%-10s | %-10s\n", "Tool", "Approved?");
  printf("------------------------\n");
  for (int i = 0; i < MAX; i++) {
      printf("%-10s | %s\n", tools[i], S[i] == 1 ? "YES" : "NO");
  }
  printf("\n");
}

void assignSet(SET target, int values[MAX]) {
  int ctr;
  for (ctr = 0; ctr < MAX; ctr++) {
    target[ctr] = values[ctr];
  }
}