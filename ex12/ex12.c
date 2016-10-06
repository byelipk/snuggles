#include <stdio.h>

int main(int argc, char *argv[])
{
  // Our Data
  int areas[] = {10,12,13,14,20};

  // This syntax for intializing a string set the null
  // byte at the end of the string.
  char name[] = "Zed";

  // With this initializer syntax we need to set the null byte
  // explicitly ourselves.
  char full_name[] = {
    'Z', 'e', 'd', ' ', 'A', '.', ' ', 'S', 'h', 'a', 'w', '\0'
  };

  /* The sizeof operator helps us answer the question how many bytes it takes */
  /* to store something in memory. */


  // WARNING: On some systems you may have to change the
  // %ld in this code to a %lu since it will use unsigned ints. 
  printf("The size of an int: %ld\n", sizeof(int));
  printf("The size areas: %ld\n", sizeof(areas));
  printf("The number of ints in areas: %ld\n", sizeof(areas) / sizeof(int));
  printf("The first area is %d, the 2nd %d\n", areas[0], areas[1]);

  printf("The size of a char: %ld\n", sizeof(char));
  printf("The size of name (char[]): %ld\n", sizeof(name));
  printf("The number of chars in name %ld\n",
      sizeof(name) / sizeof(char));

  printf("The size of full_name (char[]): %ld\n",
      sizeof(full_name));
  printf("The number of chars in full_name %ld\n", 
      sizeof(full_name) / sizeof(char));

  printf("name=\"%s\" and full_name=\"%s\"\n" , name, full_name);


  return 0;
}
