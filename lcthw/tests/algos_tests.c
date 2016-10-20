#include "minunit.h"
#include <lcthw/algos.h>
#include <assert.h>
#include <string.h>

char *values[] = { "XXXX", "1234", "abcd", "xjvef", "NDSS" };

#define NUM_VALUES 5


char *test_bubble_sort()
{
  int array[] = { 5, 4, 3, 1, 2 };
  int count   = sizeof(array) / sizeof(int);

  Int_bubble_sort(array, count);

  mu_assert(array[0] == 1, "Bubble sort failed on array of numbers.");
  mu_assert(array[1] == 2, "Bubble sort failed on array of numbers.");
  mu_assert(array[2] == 3, "Bubble sort failed on array of numbers.");
  mu_assert(array[3] == 4, "Bubble sort failed on array of numbers.");
  mu_assert(array[4] == 5, "Bubble sort failed on array of numbers.");

  return NULL;
}

char *test_merge_sort()
{
  int array[] = { 5, 3, 4, 1, 2 };
  int count   = sizeof(array) / sizeof(int);

  Int_merge_sort(array, count);

  mu_assert(array[0] == 1, "Merge sort failed on array of numbers.");
  mu_assert(array[1] == 2, "Merge sort failed on array of numbers.");
  mu_assert(array[2] == 3, "Merge sort failed on array of numbers.");
  mu_assert(array[3] == 4, "Merge sort failed on array of numbers.");
  mu_assert(array[4] == 5, "Merge sort failed on array of numbers.");

  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  mu_run_test(test_bubble_sort);
  mu_run_test(test_merge_sort);

  return NULL;
}

RUN_TESTS(all_tests);
