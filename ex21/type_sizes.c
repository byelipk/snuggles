#include <stdio.h>
#include <limits.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
  /* An 8-bit signed integer */
  /* Use lldb to see how it only takes up one byte of memory. */
  printf("----- An 8-bit signed integer -----\n");

  int8_t x     = 0;
  printf("value   = %hhd\n", x);
  printf("size    = %lu\n", sizeof(x));

  int8_t x_neg = (x -= (int8_t)1);
  printf("minus 1 = %hhd\n", x_neg);

  printf("\n");

  /* An 8-bit unsigned integer */
  /* Use lldb to make this negative and see what happens */
  /* We get an error if we try to set the raw bytcode to a negative value */
  printf("----- An 8-bit unsigned integer -----\n");

  uint8_t y      = 0;
  printf("value   = %hhu\n", y);
  printf("size    = %lu\n", sizeof(y));

  uint8_t y_neg  = (y -= (uint8_t)1);
  printf("minus 1 = %hhu\n", y_neg );

  printf("\n");

  /* A 16-bit signed integer */
  printf("----- A 16-bit signed integer -----\n");

  int16_t p = 0;
  printf("value   = %hd\n", p);
  printf("size    = %lu\n", sizeof(p));

  int16_t p_neg = (p -= (int16_t)1);
  printf("minus 1 = %hd\n", p_neg);

  printf("\n");

  /* A 16-bit unsigned integer */
  printf("----- A 16-bit unsigned integer -----\n");

  uint16_t t = 0;
  printf("value   = %hu\n", t);
  printf("size    = %lu\n", sizeof(t));

  uint16_t t_neg = (t -= (uint16_t)1);
  printf("minus 1 = %hu\n", t_neg);

  printf("\n");

  /* A 32-bit signed integer */
  printf("----- A 32-bit signed integer -----\n");

  int32_t v = 0;
  printf("value   = %d\n", v);
  printf("size    = %lu\n", sizeof(v));

  int32_t v_neg = (v -= (int32_t)1);
  printf("minus 1 = %d\n", v_neg);

  printf("\n");

  /* A 32-bit unsigned integer */
  printf("----- A 32-bit unsigned integer -----\n");

  uint32_t j = 0;
  printf("value   = %u\n", j);
  printf("size    = %lu\n", sizeof(j));

  uint32_t j_neg = (j -= (uint32_t)1);
  printf("minus 1 = %u\n", j_neg);


  printf("\n");

  /* A 64-bit signed integer */
  printf("----- A 64-bit signed integer -----\n");
  int64_t q = 0;
  printf("value   = %lld\n", q);
  printf("size    = %lu\n", sizeof(q));

  int64_t q_neg = (q -= (int64_t)1);
  printf("minus 1 = %lld\n", q_neg);
  printf("\n");

  /* A 64-bit unsigned integer */
  printf("----- A 64-bit unsigned integer -----\n");

  uint64_t z = 0;
  printf("value   = %llu\n", z);
  printf("size    = %lu\n", sizeof(z));

  uint64_t z_neg = (z -= (uint64_t)1);
  printf("minus 1 = %llu\n", z_neg);

  printf("\n");


  return 0;
}
