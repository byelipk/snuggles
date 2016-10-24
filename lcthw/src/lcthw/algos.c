#include <stdio.h>
#include <string.h>
#include <lcthw/algos.h>
#include <math.h>


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

// ALGORITHM  Quicksort(A[l..r])
//
// Desc:  Sorts a subarray by quicksort where l is the 
//        low index and r is the high index.
// Input: A subarray A[l..r] of A[0..n - 1], defined by
//        its left and right indices, l and r.
// Output: Subarray A[l..r] sorted in nondecreasing order.
//
// def Quicksort(A[l..r]) do
//   if l < r
//     s <- Partition(A[l..r]) // s is a split position
//     Quicksort(A[l..s - 1])
//     Quicksort(A[s + 1..r])
// end
int Int_quick_sort(int A[], int l, int r) 
{
  if (l < r) {
    int s = Int_partition(A, l, r);  // find the boundary
    Int_quick_sort(A, l, s - 1);     // quick sort left side
    Int_quick_sort(A, s + 1, r);     // quick sort right side
  }

  return 0;
}


// ALGORITHM  Partition(A[l..r])
//
// Desc: Partitions a subarray by using its first element as a pivot,
//       where l is the element as index position 0 and r is the last 
//       element in the array.
// Input: A subarray A[l..r] of A[0..n - 1], defined by its left and right
//        indices l and r (l < r)
// Output: A partition of A[l..r], with the split position returned as this 
//         function's value.
//
// According to the pseudo code for Partition, three situations
// may arise after the scans stop:
//
// (1) If the scanning indices i and j have crossed (i < j)
//     then we decrement i and j and resume the scans.
//
// (2) If the scanning indices have crossed over (i > j), we
//     will have partitioned the array after exchanging the
//     pivot with A[j].
//
// (3) If the scanning indices stop while pointing to the same element (i = j),
//     the value they are pointing to must be equal to the pivot.

/* def Partition(A[l..r]) do */
/*   p <- A[l]     // pivot (first element in A[l..r]) */
/*   i <- l        // index i (left to right scan) */
/*   j <- r + 1    // index j (right to left scan) */

/*   repeat */
/*     repeat i <- i + 1 until A[i] >= p */
/*     repeat j <- j - 1 until A[j] <= p */
/*     swap(A[i], A[j]) */  
/*   until i >= j */  

/*   swap(A[i], A[j])  // undo last swap when i >= j */
/*   swap(A[l], A[j]) */  

/*   return j */
/* end */

int Int_partition(int A[], int l, int r)
{
  int p = A[l];
  int i = l;
  int j = r + 1;

  // continue scanning while i < j
  do {

    // scan left side until the value at A[i] is less than the pivot
    do { i = i + 1; } while( A[i] < p );

    // scan right side until the value at A[j] is greater than the pivot
    do { j = j - 1; } while ( A[j] > p ); 

    // perform the swap
    Int_swap(A, i, j);

  } while (i < j);

  // undo last swap when i >= j
  Int_swap(A, i, j);

  // exchange pivot (p) with j to partition the array
  Int_swap(A, l, j);

  // return index position of the pivot
  return j;
}

int Int_swap(int A[], int i, int j) 
{
  int temp = A[j];
  A[j] = A[i];
  A[i] = temp;

  return 0;
}

void Int_copy(int dst[], int src[], int count)
{
  for (int i = 0, k = count - 1; i < count; i++, k++) {
    printf("Copying %d to %p\n", src[k], &dst[i]);
    dst[i] = src[k]; 
  }
}
