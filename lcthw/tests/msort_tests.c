#include "minunit.h"
#include <lcthw/msort.h>
#include <assert.h>
#include <string.h>
#include <sys/time.h>
#include <mach/mach_time.h>

char *test_merge()
{
  int Z[] = {1,2,3,4}; // expected
  int A[] = {4,3,2,1}; // original
  int B[] = {3,4};     // sorted left side
  int C[] = {1,2};     // sorted right side

  int p = sizeof(B) / sizeof(int); // size of left side
  int q = sizeof(C) / sizeof(int); // size of right side

  Int_merge(B, C, A, p, q);

  for (int i = 0; i < 4; i++) {
    mu_assert(A[i] == Z[i], "Failed to merge.");
  }

  return NULL;
}

char *test_merge_sort()
{
  int A[] = {8, 3, 2, 9, 7, 1, 5, 4};  // sort
  int Z[] = {1, 2, 3, 4, 5, 7, 8, 9};  // expected

  int size = sizeof(A) / sizeof(int);

  Int_merge_sort(A, size);

  for (int i = 0; i < size; i++) {
    mu_assert(A[i] == Z[i], "Merge sort failed.");
  }

  return NULL;
}

char *test_perf_msort()
{
  struct timeval start, end;
  unsigned int i;

  gettimeofday(&start, NULL);

  for (i = 0; i < 1000000; i++) {
    int A[10] = { 1,5,9,0,2,4,6,2,5,8 };
    int r = 10;
    Int_merge_sort(A, r);
  }

  gettimeofday(&end, NULL);

  printf("Int_merge_sort did %u calls in %.2g seconds\n", 
      i, start.tv_sec - end.tv_sec + 1E-6 * (start.tv_usec - end.tv_usec));

  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  mu_run_test(test_merge);
  mu_run_test(test_merge_sort);

  // perf tests
  mu_run_test(test_perf_msort);

  return NULL;
}

RUN_TESTS(all_tests);
