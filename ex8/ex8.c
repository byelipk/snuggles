#include <stdio.h>

int main(int argc, char *argv[])
{
  int i = 0;

  /* 
   * How can we break an IF-Statement?
   *
   * The best way to break an IF-Statement is to not handle
   * all the potential conditions in your code.
   *
   * In the code below we've neglected to write a default
   * clause that would handle cases where `argc` is greater
   * than 4 but less than 10.
   **/

  if (argc == 1) {
    printf("You only have one argument. You suck.\n");
  } else if (argc > 1 && argc < 4) {
    printf("Here are your arguments:\n");

    for (i = 0; i < argc; i++) {
      printf("%s ", argv[i]);
    }
    printf("\n");
  } else if (argc > 10) {
    printf("You have too many arguments. You suck.\n");
  }
}
