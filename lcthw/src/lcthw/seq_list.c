#include <lcthw/seq_list.h>
#include <lcthw/algos.h>

// ALGORITHM  SequentialSearch(A[0..n - 1], K)
//
// Desc:   Implements sequential search with a search key as a sentinel.
// Input:  An array A of n elements an a search key K
// Output: The index of the first element in A[0..n - 1] whose
//         value is equal to K or -1 if no such element is found.
//
// def SequentialSearch(A, K) do
//   A[n] <- K
//   i <- 0
//   while A[i] != K do
//     i <- i + 1
//   end
//   if i < n return i
//   else return -1
// end

int List_sequential_search(int list[], int size, int key)
{
  int i = 0;

  // Append key to array
  list[size - 1] = key;

  while (list[i] != key) {
    i += 1;
  }

  if (i < size) {
    return i;
  } else {
    return -1;
  }
}

int List_sequential_search_sorted(int list[], int size, int key)
{
  list[size - 1] = key; // Append key to array

  // sort the list
  int l = 0;
  int r = size;
  Int_quick_sort(list, l, r - 1);

  // iterate until we find element less than or equal to the key
  int i = 0;
  while (list[i] < key) {
    i += 1;
  }

  if (i < size) {
    return i;
  } else {
    return -1;
  }
}
