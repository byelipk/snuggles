#include "minunit.h"
#include <lcthw/algos.h>
#include <assert.h>
#include <string.h>
#include <sys/time.h>
#include <mach/mach_time.h>

char *values[] = { "XXXX", "1234", "abcd", "xjvef", "NDSS" };

#define NUM_VALUES 5


char *test_bubble_sort()
{
  int A[] = { 5, 4, 3, 1, 2 };
  int Z[] = { 1, 2, 3, 4, 5 };
  int size = sizeof(A) / sizeof(int);

  Int_bubble_sort(A, size);

  for (int i = 0; i < size; i++) {
    mu_assert(A[i] == Z[i], "Bubble sort failed.");
  }

  return NULL;
}

char *test_quick_sort()
{
  int A[] = { 1, 55, 33, 23, 99, 0, 123, 2524, 43, 54, 1 }; // array to sort
  int Z[] = { 0, 1, 1, 23, 33, 43, 54, 55, 99, 123, 2524 }; // expected

  int l = 0;
  int r = sizeof(A) / sizeof(int);

  Int_quick_sort(A, l, r - 1);

  for (int i = 0; i < r; i++) {
    mu_assert(A[i] == Z[i], "Quick sort failed.");
  }

  return NULL;
}

char *test_perf_qsort()
{
  struct timeval start, end;
  unsigned int i;

  gettimeofday(&start, NULL);

  for (i = 0; i < 1000000; i++) {
    int A[10] = { 1,5,9,0,2,4,6,2,5,8 };
    int l = 0;
    int r = 10;
    Int_quick_sort(A, l, r - 1);
  }

  gettimeofday(&end, NULL);

  printf("Int_quick_sort did %u calls in %.2g seconds\n", 
      i, start.tv_sec - end.tv_sec + 1E-6 * (start.tv_usec - end.tv_usec));

  return NULL;
}


char *all_tests()
{
  mu_suite_start();

  mu_run_test(test_bubble_sort);
  mu_run_test(test_quick_sort);

  // perf tests
  mu_run_test(test_perf_qsort);

  return NULL;
}

RUN_TESTS(all_tests);
