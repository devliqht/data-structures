#include <stdio.h>
#include <stdlib.h>

#define N 8

void countingSort(int arr[], int n, int place);
void radixSort(int arr[], int n);
void printArr(int arr[], int n);

int main(void) {
	int arr[N] = {170, 45, 75, 90, 802, 24, 2, 66};

	printf("Before: ");
	printArr(arr, N);

	radixSort(arr, N);

	printf("After:  ");
	printArr(arr, N);

	return 0;
}

// Counting sort on a specific place value (1, 10, 100, ...)
void countingSort(int arr[], int n, int place) {
	int output[n];
	int count[10] = {0};

	for (int i = 0; i < n; i++) {
		int digit = (arr[i] / place) % 10;
		count[digit]++;
	}

	for (int i = 1; i < 10; i++) {
		count[i] += count[i - 1];
	}

	for (int i = n - 1; i >= 0; i--) {
		int digit = (arr[i] / place) % 10;
		output[count[digit] - 1] = arr[i];
		count[digit]--;
	}

	for (int i = 0; i < n; i++) {
		arr[i] = output[i];
	}
}

void radixSort(int arr[], int n) {
	int max = arr[0];
	for (int i = 1; i < n; i++) {
		if (arr[i] > max) max = arr[i];
	}

	for (int place = 1; max / place > 0; place *= 10) {
		countingSort(arr, n, place);
	}
}

void printArr(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}
