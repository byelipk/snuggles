#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "dbg.h"

#define MAX_DATA 100


int read_string(char **out_string, int max_buffer)
{
  /* The calloc() function contiguously allocates enough space for `count` 
  *  objects that are `size` bytes of memory each and returns a pointer to 
  *  the allocated memory. The allocated memory is filled with bytes of 
  *  value zero.  */


  /* We increment `max_buffer` by 1 because the default buffer size is 0. 
   * On the chance we do not pass in a buffer size to `read_scan` we will
   * want to read at least 1 byte. */
  *out_string = calloc(1, max_buffer + 1);
  check_mem(*out_string);

  char *result = fgets(*out_string, max_buffer, stdin);
  check(result != NULL, "Input error.");

  return 0;

error:
  if (*out_string) free(*out_string);
  *out_string = NULL;
  return -1;
}

int read_int(int *out_int)
{
  char *input = NULL;
  int rc = read_string(&input, MAX_DATA);
  check(rc == 0, "Failed to read number.");

  *out_int = atoi(input);

  free(input);

  return 0;

error:
  if (input) free(input);
  return -1;
}

/* USAGE: read_scan("%c", &address); */
/* USAGE: read_scan("%d", &address); */
/* USAGE: read_scan("%s", MAX_DATA, &address); */
int read_scan(const char *fmt, ...)
{
  int i  = 0;
  int rc = 0;
  int  *out_int     = NULL;
  char *out_char    = NULL;
  char **out_string = NULL;
  int max_buffer    = 0;

  va_list argp;
  va_start(argp, fmt);

  for (i = 0; fmt[i] != '\0'; i++) {

    if (fmt[i] == '%') {
      // Increment i so we can run a switch statement 
      // on the char after the % sign to determine what
      // kind of operation to perform.
      i++; 

      switch(fmt[i]) {

        case '\0':
          sentinel("Invalid format, you ended with %%.");
          break;

        case 'd':
          out_int = va_arg(argp, int *);
          rc = read_int(out_int);
          check(rc == 0, "Failed to read int.");
          break;

        case 'c':
          out_char = va_arg(argp, char *);
          *out_char = fgetc(stdin);
          break;

        case 's':
          max_buffer = va_arg(argp, int);
          out_string = va_arg(argp, char **);
          rc = read_string(out_string, max_buffer);
          check(rc == 0, "Failed to read string.");
          break;

        default:
          sentinel("Invalid format.");
      }

    } else {
      fgetc(stdin);
    }

    check(!feof(stdin) && !ferror(stdin), "Input error.");
  }

  va_end(argp);
  return 0;

error:
  va_end(argp);
  return -1;
}

int sum(int count, ...)
{
  va_list valist;

  int total = 0;

  va_start(valist, count);

  for (int i = 0; i < count; i++) {
    total += va_arg(valist, int);
  }

  va_end(valist);

  return  total;
}

int main(int argc, char *argv[])
{
  char *first_name = NULL;
  char initial     = ' ';
  char *last_name  = NULL;
  int age          = 0;
  int rc           = 0;

  printf("What's your first name? ");
  rc = read_scan("%s", MAX_DATA, &first_name);
  check(rc == 0, "Failed first name.");

  printf("What's your initial? ");
  // leaving out the newline causes a bug. try it.
  rc = read_scan("%c\n", &initial); 
  check(rc == 0, "Failed to read initial.");

  printf("What's your last name? ");
  rc = read_scan("%s", MAX_DATA, &last_name);
  check(rc == 0, "Failed last name.");

  printf("What's your age? ");
  rc = read_scan("%d", &age);
  check(rc == 0, "Failed to read age.");

  printf("---- RESULTS ----\n");
  printf("First Name: %s", first_name);
  printf("Initial: %c\n", initial);
  printf("Last Name: %s", last_name);
  printf("Age: %d\n", age);

  free(first_name);
  free(last_name);

  printf("---- FUN WITH VAR_ARGS ----\n");
  int total = sum(5, 2, 2, 2, 2, 2);
  check(total == 10, "Something is not right. %d.", total);
  printf("The total is %d\n", total);

  return 0;
error:
  return -1;
}
