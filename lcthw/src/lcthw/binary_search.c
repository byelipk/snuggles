#include <math.h>
#include <lcthw/binary_search.h>

// ALGORITHM  BinarySearch(A[0..n - 1], K)
//
// Desc:  Implements nonrecursive binary search where 
//        A[0..n - 1] is a sorted list and K is the value 
//        we're searching for.
//
// Input: An array A[0..n - 1] sorted in ascending order and
//        a search key K.
//
// Output: An index of the array's element that is equal to K
//         or -1 if there is no such element.
//
//
// def BinarySearch do
//   i <- 0;
//   r <- n - 1;
//
//   while l <= r do
//     m <- FLOOR((l + r) / 2)
//     if K = A[m] return m
//     else if K < A[m] r <- m - 1
//     else l <- m + 1
//   end
//
//   return -1
// end
int Int_bsearch(int A[], int n, int k)
{
  int l = 0;      // left side iterator
  int r = n - 1;  // right side iterator

  while (l <= r) {
    int m = floor((l + r) / 2); // find the middle element

    if      (k == A[m]) { return m;  }  // FOUND IT!
    else if (k < A[m])  { r = m - 1; }  // keep scanning right
    else                { l = m + 1; }  // keep scanning left
  }

  return -1; // NO LUCK...
}
