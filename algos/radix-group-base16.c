#include <stdio.h>
#include <stdlib.h>

#define N 8

void countingSortBase16(int arr[], int n, int shift);
void radixSortBase16(int arr[], int n);
void printArr(int arr[], int n);

int main(void) {
  int arr[N] = {170, 45, 75, 90, 802, 24, 2, 66};

  printf("Before: ");
  printArr(arr, N);

  radixSortBase16(arr, N);

  printf("After:  ");
  printArr(arr, N);

  return 0;
}

// Counting sort on a specific 4-bit chunk
void countingSortBase16(int arr[], int n, int shift) {
  int output[n];
  int count[16] = {0}; 

  for (int i = 0; i < n; i++) {
    int digit = (arr[i] >> shift) & 0xF; 
    count[digit]++;
  }

  for (int i = 1; i < 16; i++) {
    count[i] += count[i - 1];
  }

  for (int i = n - 1; i >= 0; i--) {
    int digit = (arr[i] >> shift) & 0xF;
    output[count[digit] - 1] = arr[i];
    count[digit]--;
  }

  for (int i = 0; i < n; i++) {
    arr[i] = output[i];
  }
}

void radixSortBase16(int arr[], int n) {
  int max = arr[0];
  for (int i = 1; i < n; i++) {
    if (arr[i] > max)
      max = arr[i];
  }

  for (int shift = 0; (max >> shift) > 0; shift += 4) {
    countingSortBase16(arr, n, shift);
  }
}

void printArr(int arr[], int n) {
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}
