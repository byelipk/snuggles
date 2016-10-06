#include <stdio.h>

/* Program execution 
 *
 * line 18 - Initialize counter to 5.
 * line 20 - Check condition. Perform a jump to line 40.
 * line 41 - Print to stdout.
 * line 43 - Check condition. At this point the do-while loop has
 *           control of program execution so the typical switch
 *           statement semantics no longer apply.
 * line 29 - Begin another loop. This time each case statement will
 *           be executed. Remember, we've already performed the jump. */


int main(int argc, char *argv[])
{

  int count = 5;

  switch (3) {


    case 0:

      printf("Skip this!\n");

    do {

      printf("Looping!\n");

      /* The C standard allows us to nest case statements */
      /* inside a do-while loop */

      case 1:
        printf("1\n");

      case 2:
        printf("2\n");

      case 3:
        printf("3\n");
    
    } while (--count > 0);

    default:

      printf("Can't skip this!\n");

  }

  return 0;
}
