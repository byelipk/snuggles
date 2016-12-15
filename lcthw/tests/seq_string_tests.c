#include <lcthw/seq_string.h>
#include "minunit.h"

char *test_seq_search()
{
  char *string = "How are you doing this fine election eve?";
  char *pattern = "election";

  int result = String_sequential_search(string, pattern);

  mu_assert(result == 28, "Expected to find pattern, but did not.");

  return NULL;
}

char *test_seq_search_no_match()
{
  char *string = "Hello";
  char *pattern = "nice";

  int result = String_sequential_search(string, pattern);

  mu_assert(result == -1, "Expected no match, but there was a match.");

  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  mu_run_test(test_seq_search);
  mu_run_test(test_seq_search_no_match);

  return NULL;
}

RUN_TESTS(all_tests);
