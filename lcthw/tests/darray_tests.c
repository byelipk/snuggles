#include "minunit.h"
#include <string.h>
#include <lcthw/darray.h>

static DArray *array = NULL;
static int *val1 = NULL;
static int *val2 = NULL;

char *test_create()
{
  array = DArray_create(sizeof(int), 100);
  mu_assert(array != NULL, "DArray_create failed.");
  mu_assert(array->contents != NULL, "DArray contents are wrong.");
  mu_assert(array->end == 0, "DArray end isn't at the right spot.");
  mu_assert(array->element_size == sizeof(int), "DArray element size is wrong.");
  mu_assert(array->max == 100, "DArray max is wrong.");

  return NULL;
}

char *test_destroy()
{
  DArray_destroy(array);

  return NULL;
}

char *test_new()
{
  val1 = DArray_new(array);
  mu_assert(val1 != NULL, "Failed to make a new element.");

  val2 = DArray_new(array);
  mu_assert(val2 != NULL, "Failed to make a new element.");

  return NULL;
}

char *test_set()
{
  DArray_set(array, 0, val1);
  DArray_set(array, 1, val2);

  return NULL;
}

char *test_get()
{
  mu_assert(DArray_get(array, 0) == val1, "Wrong first value.");
  mu_assert(DArray_get(array, 1) == val2, "Wrong second value.");

  return NULL;
}

char *test_remove()
{
  int *val_check = DArray_remove(array, 0);
  mu_assert(val_check != NULL, "Should not get NULL.");
  mu_assert(*val_check == *val1, "Should get first value.");
  mu_assert(DArray_get(array, 0) == NULL, "Element 0 should be gone.");
  DArray_free(val_check);

  val_check = DArray_remove(array, 1);
  mu_assert(val_check != NULL, "Should not get NULL.");
  mu_assert(*val_check == *val2, "Should get first value.");
  mu_assert(DArray_get(array, 1) == NULL, "Element 1 should be gone.");
  DArray_free(val_check);

  return NULL;
}

char *test_expand_contract()
{
  int old_max = array->max;

  DArray_expand(array);
  mu_assert((unsigned int)array->max == old_max + array->expand_rate,
      "Wrong size after expand.");

  DArray_contract(array);
  mu_assert((unsigned int)array->max == array->expand_rate + 1,
      "Should stay at the expand_rate at least.");

  DArray_contract(array);
  mu_assert((unsigned int)array->max == array->expand_rate + 1,
      "Should stay at the expand_rate at least.");

  return NULL;
}

char *test_push_pop()
{
  int i = 0;
  for (i = 0; i < 1000; i++) {
    int *val = DArray_new(array);
    *val = i * 333;
    DArray_push(array, val);
  }

  mu_assert(array->max == 1201, "Wrong max size.");

  for (i = 999; i >= 0; i--) {
    int *val = DArray_pop(array);
    mu_assert(val != NULL, "Shouldn't get a NULL.");
    mu_assert(*val == i * 333, "Wrong value.");
    DArray_free(val);
  }

  return NULL;
}

char *test_lifecycle()
{
  size_t initial_max = 5;

  // Create an array
  DArray *numbers = DArray_create(sizeof(int), initial_max);

  mu_assert(numbers->max == 5, "Expected max size to be 5.");

  // Fill it with some numbers
  for (int i = 0; i < 5; i++) {
    int *val = DArray_new(numbers);
    *val = i;
    DArray_push(numbers, val);
  }

  mu_assert(numbers->max == 305, "Wrong max size.");

  // Get the values
  mu_assert(*(int *)DArray_get(numbers, 0) == 0, "Element 0 should equal 0.");
  mu_assert(*(int *)DArray_get(numbers, 1) == 1, "Element 1 should equal 1.");
  mu_assert(*(int *)DArray_get(numbers, 2) == 2, "Element 2 should equal 2.");
  mu_assert(*(int *)DArray_get(numbers, 3) == 3, "Element 3 should equal 3.");
  mu_assert(*(int *)DArray_get(numbers, 4) == 4, "Element 4 should equal 4.");

  // Set a new value, then get it
  int *new_val = DArray_new(numbers);
  *new_val = 99;
  DArray_set(numbers, 0, new_val);

  int *el = DArray_get(numbers, 0);
  mu_assert(*el == 99, "Element 0 should equal 99.");

  // Pop off all the elements
  for (int i = 4; i >= 0; i--) {
    int *val = DArray_pop(numbers);
    mu_assert(val != NULL, "Shouldn't get a NULL.");

    /* printf("[%d] Value at %p is %d\n", i, val, *val); */
    if (i == 0) {
      mu_assert(*val == 99, "Wrong value.");
    } else {
      mu_assert(*val == i, "Wrong value.");
    }
    DArray_free(val);
  }

  DArray_clear_destroy(numbers);

  return NULL;
}

char *test_can_handle_strings()
{
  char *str1 = "Hello";
  char *str2 = "world";

  // Create the array
  DArray *strings = DArray_create(sizeof(char), 3);

  // Add strings to the array
  char *el1 = DArray_new(strings);
  char *el2 = DArray_new(strings);

  // Set values of new array elements 
  el1 = str1;
  el2 = str2;

  // Push elements onto array
  DArray_push(strings, el1);
  DArray_push(strings, el2);

  // Make some assertions
  mu_assert(DArray_count(strings) == 2, "Wrong count.");
  mu_assert(strcmp(DArray_get(strings, 0), str1) == 0, "Expected 'Hello'");
  mu_assert(strcmp(DArray_get(strings, 1), str2) == 0, "Expected 'World'");

  // Check this will work with const char *
  DArray_push(strings, "AGAIN!");
  mu_assert(DArray_count(strings) == 3, "Expected count == 3.");
  mu_assert(strcmp(DArray_get(strings, 2), "AGAIN!") == 0, "Expected 'AGAIN!'");

  // Destroy the array. We do not need to clear it because
  // we're not storing the string data on the heap.
  DArray_destroy(strings);

  return NULL;
}

char *test_first_last()
{
  DArray *array = DArray_create(sizeof(int), 5);

  for (int i = 0; i < 5; i++) {
    int *val = DArray_new(array);
    *val = i;
    // NOTE
    // A bug occurs when we push elements into the array that
    // have no been provisioned via DArray_new
    DArray_push(array, val);
  }

  mu_assert(*(int *)DArray_first(array) == 0, "Expected 0.");
  mu_assert(*(int *)DArray_last(array) == 4, "Expected 4.");

  DArray_destroy(array);

  return NULL;
}


char *test_last()
{
  DArray *array = DArray_create(sizeof(int), 5);

  for (int i = 0; i < 5; i++) {
    int val = i;
    DArray_push(array, &val);
  }

  mu_assert(*(int *)DArray_last(array) == 4, "Expected 4.");

  DArray_destroy(array);

  return NULL;
}

char *test_end_count()
{
  DArray *array = DArray_create(sizeof(char), 5);

  char *str1 = DArray_new(array);
  char *str2 = DArray_new(array);

  str1 = "Hello";
  str2 = "World";

  DArray_push(array, str1);
  DArray_push(array, str2);

  mu_assert(DArray_end(array) == 2, "Expected 2 (end).");
  mu_assert(DArray_count(array) == 2, "Expected 2 (count).");

  DArray_destroy(array);

  return NULL;

}

char *test_max()
{
  DArray *array = DArray_create(sizeof(char), 2);

  mu_assert(DArray_max(array) == 2, "Expected 2.");

  char *str1 = DArray_new(array);
  char *str2 = DArray_new(array);

  str1 = "Hello";
  str2 = "World";

  DArray_push(array, str1);
  DArray_push(array, str2);

  mu_assert(DArray_max(array) == 302, "Expected 302.");

  DArray_destroy(array);

  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  // tests will go here
  mu_run_test(test_create);
  mu_run_test(test_new);
  mu_run_test(test_set);
  mu_run_test(test_get);
  mu_run_test(test_remove);
  mu_run_test(test_expand_contract);
  mu_run_test(test_push_pop);
  mu_run_test(test_destroy);

  // my special tests
  mu_run_test(test_lifecycle);
  mu_run_test(test_can_handle_strings);

  mu_run_test(test_first_last);
  mu_run_test(test_end_count);
  mu_run_test(test_max);

  return NULL;
}

RUN_TESTS(all_tests);
