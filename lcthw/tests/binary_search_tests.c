#include "minunit.h"
#include <assert.h>
#include <lcthw/binary_search.h>
#include <lcthw/algos.h>

char *test_bsearch()
{
  int list[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  int result = Int_bsearch(list, 10, 7);

  mu_assert(result == 6, "Failed to find element with bsearch.");

  return NULL;
}

char *test_bsearch_unsorted_list()
{
  int list[5] = {5, 3, 2, 1, 4};
  int size    = sizeof(list) / sizeof(int);
  int result = Int_bsearch(list, size, 3);

  mu_assert(result == -1, "Expected to not find element in unsorted list.");

  return NULL;
}

char *test_bsearch_with_quicksort()
{
  int list[5] = {5, 3, 2, 1, 4};
  int size    = sizeof(list) / sizeof(int);
  
  int l = 0;
  int r = size;
  Int_quick_sort(list, l, r - 1);

  int result = Int_bsearch(list, size, 3);

  mu_assert(result == 2, "Expected find element in sorted list.");

  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  mu_run_test(test_bsearch);
  mu_run_test(test_bsearch_unsorted_list);
  mu_run_test(test_bsearch_with_quicksort);

  return NULL;
}

RUN_TESTS(all_tests);
