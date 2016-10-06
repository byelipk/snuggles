#include <stdio.h>

/* What does this do? */
/* ./ex13 `ruby -e "puts 'a' * 1000000"` */

int main(int argc, char *argv[])
{
  int i = 0;

  // go through each string in argv
  // why am i skipping argv[0]?
  for (i = 0; i < argc; i++) {
    printf("arg %d: %s\n", i, argv[i]);

    /* Very insecure -- try it! */
    /* printf(argv[i]); */
  }

  // How would you create a two-dimensional
  // array of strings?
  //
  // We do it by combining the `char *str` syntax and
  // the `char str[]` syntax together.
  char *states[] = {
    "Massachusetts", "California", "Texas", NULL, "Oregon"
  };

  int num_states = 5;

  /* What is the effect of this line of code? */
  states[1] = argv[19];

  for (i = 0; i < num_states; i++) {
    printf("state %d: %s\n", i, states[i]);
  }

  return 0;
}
