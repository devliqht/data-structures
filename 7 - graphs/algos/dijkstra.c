#include <stdio.h>
#include <stdlib.h>

#define INT_MAX 9999
#define MAX 5
#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef int Set[MAX];
typedef int AM[MAX][MAX];
int* dijkstra(int SV, AM C);

int main(void) {
	AM A = {
		{INT_MAX, 10, INT_MAX, 30, 100},
		{INT_MAX, INT_MAX, 50, INT_MAX, INT_MAX},
		{20, INT_MAX, INT_MAX, INT_MAX, 10},
		{INT_MAX, INT_MAX, 20, INT_MAX, 60},
		{INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX}
	};
	
	int* p = dijkstra(2, A);
	printf("The cost of the shortest paths: ");
	for (int i = 0; i < 5; i++) {
		printf("%d, ", p[i]);
	}
	
	return 0;
}

int* dijkstra(int SV, AM C) {
	int* D = (int*)malloc(sizeof(int) * MAX);
	if (D != NULL) {
		Set S = {0};
		S[SV] = 1; // Bit-vector representation of 2 as our source vertex
		for (int i = 0; i < 5; i++) {
			D[i] = C[SV][i]; // Initialize D
		}
		D[SV] = 0; // path of source vertex to itself is 0a
		
		for (int idx = 1; idx < MAX; idx++) {
			int s_idx = -1;
			for (int jdx = 0; jdx < MAX; jdx++) { // We find the smallest index
				if (S[jdx] == 0) {
					if (s_idx == -1 || (D[jdx] < D[s_idx])) s_idx = jdx;		
				}
			}
			S[s_idx] = 1; // Mark the smallest index as visited
			for (int kdx = 0; kdx < MAX; kdx++) {
				if (S[kdx] == 0) { // Only visit the unvisited nodes
					D[kdx] = MIN(D[kdx], D[s_idx] + C[s_idx][kdx]);
				}
			}
		}
	}
	return D;
}