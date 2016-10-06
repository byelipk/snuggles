#include <stdio.h>

int main()
{
  printf("%c\n", "hello"[0]);

  "hello"[0] = 'H';

  return 0;
}
