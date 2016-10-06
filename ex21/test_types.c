#include "Unity/src/unity.h"
#include <limits.h>

void test_sizeof_int()
{
  TEST_ASSERT(sizeof(int) == 4);
}

void test_sizeof_double()
{
  TEST_ASSERT(sizeof(double) == 8);
}

void test_sizeof_float()
{
  TEST_ASSERT(sizeof(float) == 4);
}

void test_sizeof_char()
{
  TEST_ASSERT(sizeof(char) == 1);
}

void test_sizeof_void()
{
  TEST_ASSERT_EQUAL_INT32(1, sizeof(void));
}

void test_sizeof_enum()
{
  enum { RED, YELLOW, BLUE } Colors;

  TEST_ASSERT_EQUAL_INT32(4, sizeof(RED));
  TEST_ASSERT_EQUAL_INT32(4, sizeof(YELLOW));
  TEST_ASSERT_EQUAL_INT32(4, sizeof(BLUE));
}

void test_sizeof_unsigned_int()
{
  unsigned int n = 0;

  TEST_ASSERT_EQUAL_INT32(4, sizeof(n));
}

void test_unsigned_int_cannot_be_negative()
{
  unsigned int n = 0;

  TEST_ASSERT(n - 1 > 0);
}

void test_unsigned_int_upper_bound()
{
  unsigned int n = 0;

  TEST_ASSERT_EQUAL_INT32(n - 1, UINT_MAX);
}

void test_sizeof_signed_int()
{
  signed int n = 0;

  TEST_ASSERT_EQUAL_INT32(4, sizeof(n));
}

void test_signed_int_can_be_negative()
{
  signed int n = INT_MIN;

  TEST_ASSERT(n < 0);

}

void test_signed_int_halves_upper_bound()
{
  signed int n = INT_MAX;

  TEST_ASSERT_EQUAL_INT32(n, UINT_MAX / 2);
}

void test_sizeof_long_int()
{
  long int n = LONG_MAX;

  TEST_ASSERT_EQUAL_INT32(8, sizeof(n));
}

void test_long_int_is_larger_than_unsigned_int()
{
  TEST_ASSERT(LONG_MAX > UINT_MAX);
}

void test_sizeof_short_int()
{
  TEST_ASSERT_EQUAL_INT32(2, sizeof(short int));
}

void test_short_int_is_half_the_size_of_signed_int()
{
  TEST_ASSERT_EQUAL_INT32(sizeof(short int), sizeof(signed int) / 2);
}

int main(int argc, char *argv[])
{
  UNITY_BEGIN();

  /* Available data types */
  RUN_TEST(test_sizeof_int);
  RUN_TEST(test_sizeof_double);
  RUN_TEST(test_sizeof_float);
  RUN_TEST(test_sizeof_char);
  RUN_TEST(test_sizeof_void);
  RUN_TEST(test_sizeof_enum);

  /* Type modifiers */
  RUN_TEST(test_sizeof_unsigned_int);
  RUN_TEST(test_unsigned_int_cannot_be_negative);
  RUN_TEST(test_unsigned_int_upper_bound);

  RUN_TEST(test_sizeof_signed_int);
  RUN_TEST(test_signed_int_can_be_negative);
  RUN_TEST(test_signed_int_halves_upper_bound);

  RUN_TEST(test_sizeof_long_int);
  RUN_TEST(test_long_int_is_larger_than_unsigned_int);

  RUN_TEST(test_sizeof_short_int);
  RUN_TEST(test_short_int_is_half_the_size_of_signed_int);

  /* Type qualifiers */
  /* const */
  /* volatile */
  /* register */

  return UNITY_END();
}
