#include <stdio.h>
#include <ctype.h>
#include "dbg.h"


/* NOTE 
 * 
 * To compile and link this program run the following steps:
 *
 * # Compile the source code into an object file
 * cc -c libex29.c -o libex29.o 
 *
 * # Create a shared library from the object file. The .so
 * # file is dynamic which allows programs to reference
 * # the library on the fly rather than loading all of the
 * # library's code on boot.
 * cc -shared -o libex29.so libex29.o 
 *
 * # Compile ex29 into a binary, making sure to link the dynamic
 * # loading library.
 * cc -Wall -g -DNDEBUG ex29.c -ldl -o ex29 */


int print_a_message(const char *msg, size_t count)
{
  printf("A STRING: %s\n", msg);
  printf("BYTES: %lu\n", count);

  return 0;
}


int uppercase(const char *msg, size_t count)
{
  size_t i = 0;

  for (i = 0; i <= count; i++) {
    printf("%c", toupper(msg[i]));
  }

  printf("\n");

  return 0;
}

int lowercase(const char *msg, size_t count)
{
  size_t i = 0;

  for (i = 0; i <= count; i++) {
    printf("%c", tolower(msg[i]));
  }

  printf("\n");

  return 0;
}

int fail_on_purpose(const char *msg, size_t count)
{
  msg   = NULL;
  count = 0;

  return 1; 
}

