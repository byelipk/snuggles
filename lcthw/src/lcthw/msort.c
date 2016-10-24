#include <stdio.h>
#include <string.h>
#include <math.h>
#include <lcthw/msort.h>

void Int_copy(int dst[], int src[], int i_start, int k_start, int i_end)
{
  for (int i = i_start, k = k_start; i < i_end; i++, k++) {
    dst[i] = src[k];
  }
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
// def Mergesort do
//   if n > 1
//     copy A[0..FLOOR(n / 2) - 1] to B[0..FLOOR(n / 2) - 1]
//     copy A[FLOOR(n / 2)..n - 1] to C[0..FLOOR(n / 2) - 1]
//     Mergesort(B[0..FLOOR(n/2) - 1])
//     Mergesort(C[0..FLOOR(n/2) - 1])
//     Merge(B, C, A)
//   end
// end
int Int_merge_sort(int A[], int n)
{
  // We only perform the sort if there are more than
  // one element in the array.
  if (n > 1) {
    int p = floor(n / 2); // size of B[]
    int q = n - p;        // size of C[]

    int B[p]; // array of size p
    int C[q]; // array of size q

    Int_copy(B, A, 0, 0, p);
    Int_copy(C, A, 0, q, q);

    Int_merge_sort(B, p);
    Int_merge_sort(C, q);

    Int_merge(B, C, A, p, q);
  }

  return 0;
}

// ALGORITHM  Merge(B[0..p - 1], C[0..q - 1], A[0..p + q - 1])
//
// Desc:   Merges two sorted arrays into one sorted array, where
//         p is the number of elements in array B and q is the 
//         number of elements in array C.
// Input:  Arrays B[0..p - 1] and C[0..q - 1], both sorted.
// Output: Sorted array A[0..p + q - 1] of the elements of B and C.
//
// def Merge do
//   i <- 0; j <- 0; k <- 0
//   while i < p and j < q do
//     if B[i] <= C[j]
//       A[k] = B[i]
//       i <- i + 1
//     else
//       A[k] = C[j]
//       i <- i + 1
//     end
//     k <- k + 1
//   end
//
//   if i == p
//     copy C[j..q - 1] to A[k..p + q - 1]
//   else
//     copy B[i..p - 1] to A[k..p + q - 1]
//   end
// end
//
int Int_merge(int B[], int C[], int A[], int p, int q)
{
  int i = 0;  // iterator for B
  int j = 0;  // iterator for C
  int k = 0;  // iterator for A

  // perform swap
  while (i < p && j < q) {
    if (B[i] <= C[j]) { 
      A[k] = B[i]; i = i + 1; 
    } else { 
      A[k] = C[j]; j = j + 1; 
    }
    k = k + 1;
  }

  // copy remaining elements to end of A
  if (i == p) { 
    for (int x = j, y = k; x < q; x++, y++) {
      A[y] = C[x];
    }
  } 
  else { 
    for (int x = i, y = k; x < p; x++, y++) {
      A[y] = B[x];
    }
  }

  return 0;
}


