#include <lcthw/string_match.h>
#include "minunit.h"

char *test_shift_table()
{
  bstring str = bfromcstr("Hi, how are you doing?");

  char * result = ShiftTable(str);

  bdestroy(str);
  
  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  mu_run_test(test_shift_table);

  return NULL;
}

RUN_TESTS(all_tests);
