#include "minunit.h"
#include <assert.h>
#include <string.h>
#include <lcthw/bstrlib.h>
#include <lcthw/bstraux.h>

char *test_bfromcstr()
{
  bstring b = bfromcstr("Hello, BSTRING!");

  printf("%s\n", b->data);

  return NULL;
}

char *test_bstrcmp()
{
  bstring b0 = bfromcstr("greater");
  bstring b1 = bfromcstr("GREATER");
  mu_assert(bstrcmp(b0, b1) > 0, "Failed to compare bstrings");

  b0 = bfromcstr("equal");
  b1 = bfromcstr("equal");
  mu_assert(bstrcmp(b0, b1) == 0, "Failed to compare bstrings");

  b0 = bfromcstr("LESS");
  b1 = bfromcstr("less");
  mu_assert(bstrcmp(b0, b1) < 0, "Failed to compare bstrings");

  return NULL;
}

char *test_bstrncmp()
{
  bstring b0 = bfromcstr("greater");
  bstring b1 = bfromcstr("greeter");
  mu_assert(bstrncmp(b0, b1, 3) == 0, "Failed to compare first 3 bytes of bstring.");

  return NULL;
}

char *test_bstricmp()
{
  bstring b0 = bfromcstr("GREAT");
  bstring b1 = bfromcstr("great");
  mu_assert(bstricmp(b0, b1) == 0, "Failed to compare upper and lowercase string.");

  return NULL;
}

char *test_bdestroy()
{
  bstring b0 = bfromcstr("Hello!");

  mu_assert(bdestroy(b0) == 0, "Failed to destroy bstring.");

  return NULL;
}

char *test_bfindreplace()
{
  bstring b0 = bfromcstr("Replace me now. Thanks!");
  bstring b1 = bfromcstr("o");
  bstring b2 = bfromcstr("e");
  int position = 0;

  mu_assert(bfindreplace(b0, b1, b2, position) == 0, "Failed to find and replace bstring.");

  return NULL;
}

char *test_slen()
{
  bstring b0 = bfromcstr("John");

  mu_assert(blength(b0) == 4, "Failed to get size of bstring.");

  return NULL;
}

char *test_breverse()
{
  bstring b0 = bfromcstr("lolz");
  bstring b1 = bfromcstr("zlol");

  bReverse(b0);

  mu_assert(bstrcmp(b0, b1) == 0, "Failed to reverse bstring.");

  return NULL;
}

char *test_bconcat()
{
  bstring b0 = bfromcstr("Hello this is some text for you to search. I hope it goes well.");
  bstring b1 = bfromcstr("I hope it goes well.");

  bconcat(b0, b1);

  mu_assert(binstr(b0, 0, b1) > 0, "Did not find substring.");

  return NULL;
}

char *test_binstr()
{
  bstring b0 = bfromcstr("Hello");
  bstring b1 = bfromcstr("ello");
  bstring b2 = bfromcstr("NOPE");

  mu_assert(binstr(b0, 0, b1) > 0, "Did not find substring.");
  mu_assert(binstr(b0, 0, b2) == BSTR_ERR, "Did not find substring.");

  return NULL;
}


char *all_tests()
{
  mu_suite_start();

  mu_run_test(test_bfromcstr);
  mu_run_test(test_bstrcmp);
  mu_run_test(test_bstrncmp);
  mu_run_test(test_bstricmp);
  mu_run_test(test_bdestroy);
  mu_run_test(test_bfindreplace);
  mu_run_test(test_slen);
  mu_run_test(test_breverse);
  mu_run_test(test_bconcat);
  mu_run_test(test_binstr);

  return NULL;
}

RUN_TESTS(all_tests);
