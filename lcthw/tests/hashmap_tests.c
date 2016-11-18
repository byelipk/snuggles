#include "minunit.h"
#include <lcthw/hashmap.h>
#include <assert.h>
#include <lcthw/bstrlib.h>

Hashmap *map = NULL;
static int traverse_called = 0;
struct tagbstring test1 = bsStatic("test data 1");
struct tagbstring test2 = bsStatic("test data 2");
struct tagbstring test3 = bsStatic("test data 3");
struct tagbstring expect1 = bsStatic("THE VALUE 1");
struct tagbstring expect2 = bsStatic("THE VALUE 2");
struct tagbstring expect3 = bsStatic("THE VALUE 3");

static int traverse_good_cb(HashmapNode *node)
{
  debug("KEY: %s", bdata((bstring) node->key));
  traverse_called++;
  return 0;

  if (traverse_called == 2) {
    return 1;
  } else {
    return 0;
  }
}

static int traverse_fail_cb(HashmapNode *node)
{
  debug("KEY: %s", bdata((bstring) node->key));
  traverse_called++;

  if (traverse_called == 2) {
    return 1;
  } else {
    return 0;
  }
}

char *test_create()
{
  map = Hashmap_create(NULL, NULL);
  mu_assert(map != NULL, "Failed to create map.");
  return NULL;
}

char *test_destroy()
{
  Hashmap_destroy(map);

  return NULL;
}

char *test_get_set()
{
  int rc = Hashmap_set(map, &test1, &expect1);
  mu_assert(rc == 0, "Failed to set &test1");
  bstring result = Hashmap_get(map, &test1);
  mu_assert(result == &expect1, "Wrong value for test1.");

  rc = Hashmap_set(map, &test2, &expect2);
  mu_assert(rc == 0, "Failed to set &test2");
  result = Hashmap_get(map, &test2);
  mu_assert(result == &expect2, "Wrong value for test2.");

  rc = Hashmap_set(map, &test3, &expect3);
  mu_assert(rc == 0, "Failed to set &test3");
  result = Hashmap_get(map, &test3);
  mu_assert(result == &expect3, "Wrong value for test3.");

  return NULL;
}

char *test_traverse()
{
  int rc = Hashmap_traverse(map, traverse_good_cb);
  mu_assert(rc == 0, "Failed to traverse.");
  mu_assert(traverse_called == 3, "Wrong count traverse.");

  traverse_called = 0;
  rc = Hashmap_traverse(map, traverse_fail_cb);
  mu_assert(rc == 1, "Failed to traverse.");
  mu_assert(traverse_called == 2, "Wrong count traverse for fail.");

  return NULL;
}

char *test_delete()
{
  bstring deleted = (bstring) Hashmap_delete(map, &test1);
  mu_assert(deleted != NULL, "Got NULL on delete.");
  mu_assert(deleted == &expect1, "Should get test 1.");
  bstring result = Hashmap_get(map, &test1);
  mu_assert(result == NULL, "Should delete.");

  deleted = (bstring) Hashmap_delete(map, &test2);
  mu_assert(deleted != NULL, "Got NULL on delete.");
  mu_assert(deleted == &expect2, "Should get test 2.");
  result = Hashmap_get(map, &test2);
  mu_assert(result == NULL, "Should delete.");

  deleted = (bstring) Hashmap_delete(map, &test3);
  mu_assert(deleted != NULL, "Got NULL on delete.");
  mu_assert(deleted == &expect3, "Should get test 3.");
  result = Hashmap_get(map, &test3);
  mu_assert(result == NULL, "Should delete.");

  return NULL;
}


// MY TESTS

char *test_create_destroy()
{
  // Creating a hashmap requires a comparison function
  // and hashing function.
  Hashmap *hash_table = Hashmap_create(NULL, NULL);
  Hashmap_destroy(hash_table);

  return NULL;
}

char *test_get_empty_hashmap()
{
  Hashmap *hash_table = Hashmap_create(NULL, NULL);
  bstring key = bfromcstr("A");

  void *result = Hashmap_get(hash_table, &key);

  mu_assert(result == NULL, "Expected NULL, but didn't get it.");

  Hashmap_destroy(hash_table);
  bdestroy(key);

  return NULL;
}

char *test_works_with_char_values()
{
  Hashmap *hash_table = Hashmap_create(NULL, NULL);
  mu_assert(hash_table != NULL, "Hashmap_create failed.");

  char *key = "key";
  char value = 'A';

  int rc = Hashmap_set(hash_table, &key, &value);
  mu_assert(rc == 0, "Hashmap_set failed.");

  char *result = Hashmap_get(hash_table, &key);
  mu_assert(*result == value, "Wrong value for key.");

  printf("[CHAR] %p -> %c\n", result, *result);

  Hashmap_destroy(hash_table);

  return NULL;
}

char *test_works_with_int_values()
{
  Hashmap *hash_table = Hashmap_create(NULL, NULL);
  mu_assert(hash_table != NULL, "Hashmap_create failed.");

  char *key = "age";
  int value = 31;

  int rc = Hashmap_set(hash_table, &key, &value);
  mu_assert(rc == 0, "Hashmap_set failed.");

  int *result = Hashmap_get(hash_table, &key);
  mu_assert(*result == value, "Wrong value for key.");

  Hashmap_destroy(hash_table);

  return NULL;
}

char *test_works_with_float_values()
{
  Hashmap *hash_table = Hashmap_create(NULL, NULL);
  mu_assert(hash_table != NULL, "Hashmap_create failed.");

  char *key = "my-key";
  float value = 10.98;

  printf("%p -> %s\n", &key, key);
  printf("%p -> %.02f\n", &value, value);

  int rc = Hashmap_set(hash_table, &key, &value);
  mu_assert(rc == 0, "Hashmap_set failed.");

  float *result = Hashmap_get(hash_table, &key);
  mu_assert(*result == value, "Wrong value for key.");

  Hashmap_destroy(hash_table);

  return NULL;
}

char *test_works_with_values_of_different_types()
{
  Hashmap *hash_table = Hashmap_create(NULL, NULL);
  mu_assert(hash_table != NULL, "Hashmap_create failed.");

  // keys
  char *key1 = "temp";
  char *key2 = "year";
  char *key3 = "quote";
  char *key4 = "question";

  // values
  float val1 = 10.98;
  int   val2 = 1098;
  char *val3 = "Hello world";
  bstring val4 = bfromcstr("Did you vote already?");

  // NOTE
  // Set key/value pairs by passing in the address
  // of the key variable and the address of the
  // value variable.
  int rc1 = Hashmap_set(hash_table, &key1, &val1);
  int rc2 = Hashmap_set(hash_table, &key2, &val2);
  int rc3 = Hashmap_set(hash_table, &key3, &val3);
  int rc4 = Hashmap_set(hash_table, &key4, &val4);

  mu_assert(rc1 == 0, "Hashmap_set failed to set float.");
  mu_assert(rc2 == 0, "Hashmap_set failed to set int.");
  mu_assert(rc3 == 0, "Hashmap_set failed to set string.");
  mu_assert(rc4 == 0, "Hashmap_set failed to set bstring.");

  // NOTE
  // Get pointer to value by passing in address of key variable
  float *res1  = Hashmap_get(hash_table, &key1);
  int   *res2  = Hashmap_get(hash_table, &key2);
  char  *res3  = Hashmap_get(hash_table, &key3);
  bstring res4 = Hashmap_get(hash_table, &key4);

  // NOTE
  // Compare pointer variables, not values
  mu_assert(*res1 == val1, "Wrong value for float.");
  mu_assert(*res2 == val2, "Wrong value for int.");
  mu_assert(res3 == (char *)&val3, "Wrong value for string.");
  mu_assert(res4 == (bstring)&val4, "Wrong value for bstring.");

  Hashmap_destroy(hash_table);

  return NULL;
}

char *test_updating_key_in_map()
{
  bstring key = bfromcstr("key");
  bstring old_value = bfromcstr("old data");
  bstring new_value = bfromcstr("new data");

  Hashmap *hash_table = Hashmap_create(NULL, NULL);
  mu_assert(hash_table != NULL, "Failed to create hashmap.");

  int rc = Hashmap_set(hash_table, &key, &old_value);
  mu_assert(rc == 0, "Failed to set old value.");
  mu_assert(Hashmap_get(hash_table, &key) == &old_value,
    "Failed to find old value in hashmap.");

  // Looks like our implementation of Hashmap_set will not work unless we
  // first delete the existing key. Does this cause memory problems?
  Hashmap_delete(hash_table, &key);

  rc = Hashmap_set(hash_table, &key, &new_value);
  mu_assert(rc == 0, "Failed to set new value.");
  mu_assert(Hashmap_get(hash_table, &key) == &new_value,
    "Failed to find new value in hashmap.");

  Hashmap_destroy(hash_table);

  bdestroy(key);
  bdestroy(old_value);
  bdestroy(new_value);

  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  // tests from the book
  mu_run_test(test_create);
  mu_run_test(test_get_set);
  mu_run_test(test_traverse);
  mu_run_test(test_delete);
  mu_run_test(test_destroy);

  // my tests
  mu_run_test(test_create_destroy);
  mu_run_test(test_get_empty_hashmap);
  mu_run_test(test_updating_key_in_map);
  mu_run_test(test_works_with_char_values);
  mu_run_test(test_works_with_int_values);
  mu_run_test(test_works_with_float_values);
  mu_run_test(test_works_with_values_of_different_types);

  return NULL;
}

RUN_TESTS(all_tests);
