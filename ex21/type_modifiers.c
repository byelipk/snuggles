#include <stdio.h>
#include <limits.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
  printf("Signed integers --\n");

  printf("\tMaximum values\n");

  printf("\t\t8-bit:  %d\n", INT8_MAX);
  printf("\t\t16-bit: %d\n", INT16_MAX);
  printf("\t\t32-bit: %d\n", INT32_MAX);
  printf("\t\t64-bit: %lld\n", INT64_MAX);
  printf("\n");

  printf("\tMinimum values\n");

  printf("\t\t8-bit:  %d\n", INT8_MIN);
  printf("\t\t16-bit: %d\n", INT16_MIN);
  printf("\t\t32-bit: %d\n", INT32_MIN);
  printf("\t\t64-bit: %lld\n", INT64_MIN);
  printf("\n");

  printf("Unsigned integers --\n");

  printf("\tMaximum values\n");

  printf("\t\t8-bit:  %u\n", UINT8_MAX);
  printf("\t\t16-bit: %u\n", UINT16_MAX);
  printf("\t\t32-bit: %u\n", UINT32_MAX);
  printf("\t\t64-bit: %llu\n", UINT64_MAX);
  printf("\n");

  printf("Maximum of `size_t` is %llu\n", SIZE_MAX);
  printf("Maximum value of `ptrdiff_t` is %lld\n", PTRDIFF_MAX);
  printf("Minimum value of `ptrdiff_t` is %lld\n", PTRDIFF_MIN);
  printf("Largest value for the biggest unsigned integer is %llu\n", UINTMAX_MAX);
  printf("Largest value for the biggest signed integer is %lld\n", INTMAX_MAX);
  printf("Smallest value for the biggest signed integer is %lld\n", INTMAX_MIN);

  /* For more types see: /usr/include/stdint.h */


  return 0;
}
