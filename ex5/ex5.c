#include <stdio.h>

int main(int argc, char *argv[]) 
{
  printf("C Data Operators\n");
  printf("----------------\n");

  printf("sizeof()\n");
  printf("The size of an `int` is %lu\n", sizeof(int));
  printf("The size of a `char` is %lu\n", sizeof(char));
  printf("The size of a `pointer` is %lu\n", sizeof(NULL));

  return 0;
}
