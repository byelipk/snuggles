#include <stdio.h>

int main(int argc, char *argv[])
{
  int i = 0;

  while (i < 25) {
    printf("[FORWARDS] %d\n", i);
    i++;
  }

  // Decrementing the counter let's us count backwards
  while (i > 0) {
    printf("[BACKWARDS] %d\n", i);
    i--;
  }

  while (i == 0) {
    printf("Exiting program...\n");
    i++;
  }

  return 0;
}
