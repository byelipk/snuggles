#include <lcthw/list_algos.h>
#include <lcthw/dbg.h>

inline void ListNode_swap(ListNode *a, ListNode *b)
{
  void *temp = a->value;
  a->value = b->value;
  b->value = temp;
}

int Int_bubble_sort(int array[], int n)
{
  int i = 0;
  int j = 0;

  // NOTE
  // If the array only contains one element, or it is empty,
  // it is sorted.
  if (n <= 1) {
    return 0;
  }

  int swapped = 0;
  for (i = 0; i < (n - 1); i++) {
    for (j = 0; j < (n - 1 - i); j++) {
      if (array[j + 1] < array[j]) {
        int temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
        swapped = 1;
      }
    }

    // NOTE
    // If the bubble sort makes no exchanges on its pass through
    // the algorithm can be stopped.
    if (swapped == 0) {
      printf("no swappage\n");
      break;
    }
  }

  return 0;
}

// ALGORITHM  BubbleSort(A[0..n - 1])
//
// Desc:   Sorts a given array by bubble sort,
//         where n is the number of elements in the array.
// Input:  An array A[0..n - 1] or orderable elements.
// Output: Array A[0..n-1] sorted in ascending order.
//
// for i <- 0 to n - 2 do
//     for j <- 0 to n - 2 - i do
//         if A[j + 1] < A[j]
//             swap A[j] and A[j + 1]
int List_bubble_sort(List * list, List_compare cmp)
{
  int sorted = 1;

  if (List_count(list) <= 1) {
    return 0; // already sorted
  }

  do {
    sorted = 1;
    LIST_FOREACH(list, first, next, cur) {
      if (cur->next) {
        if (cmp(cur->value, cur->next->value) > 0) {
          ListNode_swap(cur, cur->next); // swap because cur > cur->next
          sorted = 0;
        }
      }
    }
  } while(!sorted);

  return 0;
}

int List_merge_sort(List * list, List_compare cmp)
{
  return 1;
}
