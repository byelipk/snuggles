#include <lcthw/seq_list.h>
#include "minunit.h"

char *test_seq_search()
{
  int list[5] = { 1, 4, 3, 7, 0 };
  int size = 5;
  int key  = 7;

  int result = List_sequential_search(list, size, key);

  mu_assert(result == 3,
    "List_sequential_search failed to find correct index.");

  return NULL;
}

char *test_seq_search_sorted()
{
  int list[5] = { 4, 3, 2, 1, 0};
  int size = 5;
  int key  = 4;

  int result = List_sequential_search_sorted(list, size, key);

  printf("Result is %d\n", result);
  
  mu_assert(result == 3,
    "List_sequential_search_sorted failed to find correct index.");

  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  mu_run_test(test_seq_search);
  mu_run_test(test_seq_search_sorted);

  return NULL;
}

RUN_TESTS(all_tests);
