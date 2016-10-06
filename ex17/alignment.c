#include <stdio.h>

int main(int argc, char *argv[])
{
  /* Padding */
  /* How do you think these variables will be occupy bytes in memory?
   *
   * You probably think it they would occupy 13 contiguous bytes in
   * memory, wouldn't you? That is, 8 bytes for the pointer, 1 byte 
   * for the char, and 4 bytes for the integer. But that is not what
   * happens. 
   *
   * The pointer variable starts on a self-aligned 8-byte boundary -
   * this is pointer alignment.
   *
   * The storage for `c` follows immediately.
   *
   * Since `x` is an int, it has a 4-byte alignment requirement. So
   * the compiler will add 3 extra bytes between `c` and `x`. */
  char *p = "Hello";
  char c  = 'h';
  int  x  = 1;

  /* Take note of the memory addresses we print out. What pattern
   * do you notice? */

  printf("Address of `p` is %p\n", &p); // Address of `p` is 0x7fff5fbff6c8
  printf("Address of `c` is %p\n", &c); // Address of `c` is 0x7fff5fbff6c7
  printf("Address of `x` is %p\n", &x); // Address of `x` is 0x7fff5fbff6c0

  /* The memory addresses are shrinking. Why? 
   *
   * Because we're using the stack memory space and the stack 
   * grows downwards. 
   */


  return 0;
}
