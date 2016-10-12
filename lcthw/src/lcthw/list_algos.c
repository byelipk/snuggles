#include <lcthw/list_algos.h>
#include <lcthw/dbg.h>

inline void ListNode_swap(ListNode *a, ListNode *b)
{
  void *temp = a->value;
  a->value = b->value;
  b->value = temp;
}

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

List *List_merge(List *left, List *right, List_compare cmp)
{
  List *result = List_create();
  void *val = NULL;

  while(List_count(left) > 0 || List_count(right) > 0) {
    if (List_count(left) > 0 && List_count(right) > 0) {
      if (cmp(List_first(left), List_first(right)) <= 0) {
        val = List_shift(left);
      } else {
        val = List_shift(right);
      }

      List_push(result, val);
    } else if (List_count(left) > 0) {
      val = List_shift(left);
      List_push(result, val);
    } else if (List_count(right) > 0) {
      val = List_shift(right);
      List_push(result, val);
    }
  }

  return result;
}

List *List_merge_sort(List * list, List_compare cmp)
{
  List *result = NULL;

  if (List_count(list) <= 1) {
    return list;
  }

  List *left = List_create();
  List *right = List_create();
  int middle = List_count(list) / 2;

  LIST_FOREACH(list, first, next, cur) {
    if (middle > 0) {
      List_push(left, cur->value);
    } else {
      List_push(right, cur->value);
    }

    middle--;
  }

  List *sort_left = List_merge_sort(left, cmp);
  List *sort_right = List_merge_sort(right, cmp);

  if (sort_left != left) {
    List_destroy(left);
  }

  if (sort_right != right) {
    List_destroy(right);
  }

  // recursion
  result = List_merge(sort_left, sort_right, cmp);

  List_destroy(sort_left);
  List_destroy(sort_right);

  return result;
}
