/*
 * SelectionSort.c
 *
 *  based on:
 *  https://www.geeksforgeeks.org/selection-sort/
 */

#include "SelectionSort.h"

// C program to sort the array in an
// ascending order using selection sort

static void swap(int* xp, int* yp)  {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

// Function to perform Selection Sort
void selectionSort(int arr[], int n)  {
  int i, j, min_idx;

  // One by one move boundary of
  // unsorted subarray
  for (i = 0; i < n - 1; i++) {
    // Find the minimum element in
    // unsorted array
    min_idx = i;
    for (j = i + 1; j < n; j++) {
      if (arr[j] < arr[min_idx]) {
        min_idx = j;
      }
    }
    // Swap the found minimum element
    // with the first element
    swap(&arr[min_idx], &arr[i]);
  }
}
