#include <stdio.h>
#include <stdlib.h>

struct Thing {
  int value;
};

int main()
{
  struct Thing *thing = calloc(1, sizeof(struct Thing));

  thing->value = 1;

  free(thing);

  printf("%d\n", thing->value);

  return 0;
}
