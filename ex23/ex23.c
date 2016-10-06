#include <stdio.h>
#include <string.h>
#include "dbg.h"

int normal_copy(char *from, char *to, int count)
{
  int i = 0;

  for (i = 0; i < count; i++) {
    to[i] = from[i];
  }

  return i;
}

int valid_copy(char *data, int count, char expects)
{
  int i = 0;

  for (i = 0; i < count; i++) {
    if (data[i] != expects) {
      log_err("[%d] %c != %c", i, data[i], expects);
      return 0;
    }
  }

  return i;
}

/* It seems that duffs device explots that fact that you */ 
/* can run an arbitrary number of case statements nested */
/* within a parent case statement. */
int duffs_device(char *from, char *to, int count)
{
  {
    /* n is the number of code blocks to run */
    int n = (count + 7) / 8;

    printf("n is %d\n", n);
    printf("n %% 8 is %d\n", n % 8);

    switch (count % 8) {

      case 0:

        printf("case 0\n");

        do {
          /* Arbitrary case statements that don't do anything */
          case 'y':
          printf("case y\n");
          case 'z':
          printf("case z\n");

          *to++ = *from++;
          case 7:
          printf("case 7\n");
          *to++ = *from++;
          case 6:
          printf("case 6\n");
          *to++ = *from++;
          case 5:
          printf("case 5\n");
          *to++ = *from++;
          case 4:
          printf("case 4\n");
          *to++ = *from++;
          case 3:
          printf("case 3\n");
          *to++ = *from++;
          case 2:
          printf("case 2\n");
          *to++ = *from++;
          case 1:
          printf("case 1\n");
          *to++ = *from++;

          /* Arbitrary case statements that don't do anything */
          case 'a':
          printf("case a\n");
          case 'b':
          printf("case b\n");

        } while (--n > 0);
    }
  }

  return count;
}

int main(int argc, char *argv[]) 
{
  char from[1000] = {'a'};
  char to[1000]   = {'c'};

  int rc = 0;

  // setup the from to have some stuff
  // memset will write 1000 bytes into `from`
  memset(from, 'x', 1000);
  // set it to a failure mode
  // memset will write 1000 bytes into `to`
  memset(to, 'y', 1000);
  check(valid_copy(to, 1000, 'y'), "Not initialized right.");

  // use normal copy too
  rc = normal_copy(from, to, 1000);
  check(rc == 1000, "Normal copy failed: %d", rc);
  check(valid_copy(to, 1000, 'x'), "Normal copy failed");

  // reset
  memset(to, 'y', 1000);

  // use normal copy too
  rc = duffs_device(from, to, 1000);
  check(rc == 1000, "Duffs device failed: %d", rc);
  check(valid_copy(to, 1000, 'x'), "Duffs device failed");

  // reset
  memset(to, 'y', 1000);

  return 0;
error:
  return 1;
}
