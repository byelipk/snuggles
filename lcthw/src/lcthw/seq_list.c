#include <lcthw/seq_list.h>
#include <lcthw/algos.h>

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

  // iterate until we find element less than for equal to the key
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
