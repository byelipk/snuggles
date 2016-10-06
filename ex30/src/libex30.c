#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "dbg.h"

#define MAX_LEN 100

int print_a_message(const char *msg)
{
  size_t count = strnlen(msg, MAX_LEN);

  printf("A STRING: %s\n", msg);
  printf("BYTES: %lu\n", count);

  return 0;
}


int uppercase(const char *msg)
{
  size_t count = strnlen(msg, MAX_LEN);

  for (size_t i = 0; i < count; i++) {
    printf("%c", toupper(msg[i]));
  }

  printf("\n");

  return 0;
}

int lowercase(const char *msg)
{
  size_t count = strnlen(msg, MAX_LEN);

  for (size_t i = 0; i <= count; i++) {
    printf("%c", tolower(msg[i]));
  }

  printf("\n");

  return 0;
}

int fail_on_purpose(const char *msg)
{
  msg = NULL;

  return 1; 
}

