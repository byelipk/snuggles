#include <stdio.h>
#include <string.h>

int Int_merge(int B[], int C[], int A[], int p, int q);

// Brute Force
//
//
// ALGORITHM  BubbleSort(A[0..n - 1])
//
// Desc:   Sorts a given array by bubble sort,
//         where n is the number of elements in the array.
// Input:  A zero-index array of n orderable elements.
// Output: Array A[0..n - 1] sorted in ascending order.
//
// for i <- 0 to n - 2 do
//     for j <- 0 to n - 2 - i do
//         if A[j + 1] < A[j]
//             swap A[j] and A[j + 1]
int Int_bubble_sort(int array[], int n)
{
  int i = 0;
  int j = 0;

  // NOTE
  // If the array only contains one element, or it is empty,
  // then it is sorted.
  if (n <= 1) {
    return 0;
  }

  // TODO
  // If the bubble sort makes no exchanges on its pass through
  // the algorithm can be stopped.
  for (i = 0; i < (n - 1); i++) {        // outer loop
    for (j = 0; j < (n - 1 - i); j++) {  // inner loop
      if (array[j + 1] < array[j]) {     // swap
        int temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
      }
    }
  }

  return 0;
}

// Divide And Conquer
//
// ALGORITHM  Mergesort(A[0..n - 1])
//
// Desc:   Sorts a given array by recursive mergesort,
//         where n is the number of elements in the array.
// Input:  A zero-index array of n orderable elements.
// Output: Array A[0..n - 1] sorted in ascending order.
//
// if n > 1
//    copy A[0..FLOOR(n / 2) - 1] to B[0..FLOOR(n / 2) - 1]
//    copy A[FLOOR(n / 2)..n - 1] to C[0..FLOOR(n / 2) - 1]
//    Mergesort(B[0..FLOOR(n/2) - 1])
//    Mergesort(C[0..FLOOR(n/2) - 1])
//    Merge(B, C, A)
int Int_merge_sort(int A[], int n)
{
  // Empty arrays and arrays with 1 element are already sorted
  // so we return from the function here. This also helps us
  // implement this function recursively.
  if (n <= 1) {
    return 0;
  }

  int p = (n / 2); // size of first half of array A
  int q = n - p;   // size of second half of array A

  int B[p]; // temp array of size p
  int C[q]; // temp array of size q

  // copy p elements from A into B
  memcpy(B, A, (p * sizeof(int)));

  // copy q elements from A into C
  memcpy(C, &A[p], (q * sizeof(int)));

  // Recursively merge array B and C
  Int_merge_sort(B, p);
  Int_merge_sort(C, q);

  Int_merge(B, C, A, p, q);

  return 0;
}



// ALGORITHM  Merge(B[0..p - 1], C[0..q - 1], A[0..p + q - 1])
//
// Desc:   Merges two sorted arrays into one sorted array, where
//         p is the number of elements in array B and q is the 
//         number of elements in array C.
//         arrays.
// Input:  Arrays B[0..p - 1] and C[0..q - 1] both sorted
// Output: Sorted array A[0..p + q - 1] of the elements of B and C
//
// i <- 0; j <- 0; k <- 0
// while i < p and j < q do
//     if B[i] <= C[j]
//         A[k] = B[i]
//         i <- i + 1
//     else
//         A[k] = C[j]
//         i <- i + 1
//
//     k <- k + 1
//
// if i == p
//     copy C[j..q - 1] to A[k..p + q - 1]
// else
//     copy B[i..p - 1] to A[k..p + q - 1]
//
int Int_merge(int B[], int C[], int A[], int p, int q)
{
  int i = 0;
  int j = 0;
  int k = 0;

  while (i < p && j < q) {
    if (B[i] <= C[j]) {
      A[k] = B[i];
      i = i + 1;
    } else {
      A[k] = C[j];
      j = j + 1;
    }

    k = k + 1;
  }


  if (i == p) {
    memcpy(&A[k], &C[j], (q * sizeof(int)));
  } else {
    memcpy(&A[k], &B[i], (p * sizeof(int)));
  }

  return 0;
}
