#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

/* The manner in which we declare the elements determines 
 * where they will sit in memory. 
 *
 * Since we've declared a pointer to a char in first position, and
 * the size of a pointer is 8 bytes, the first 8 bytes of the 
 * Person struct will be the pointer to `name`.
 *
 * The next 4 bytes will be the `age` element. The next 4 after that 
 * will be the `height` element. The last 4 bytes will correspond to
 * the `weight` element.
 *
 * The size of all the elements in a Person struct is 8 + 4 + 4 + 4 = 20 bytes.
 * */
struct Person {
  char *name;     // Person struct has a pointer to a char called `name`
  int age;        // Person struct has an integer called `age`
  int height;     // Person struct has an integer called `height`
  int weight;     // Person struct has an integer called `weight`
};

void Person_print(struct Person who)
{
  printf("Name: %s\n", who.name);
  printf("\tAge: %d\n", who.age);
  printf("\tHeight: %d\n", who.height);
  printf("\tWeight: %d\n", who.weight);
}

int main(int argc, char *argv[])
{
  // make two people structures
  struct Person joe = {"Joe Alex", 32, 63, 140};
  struct Person tom = {"Tom Blan", 20, 72, 180};

  // print them out and where they are in memory
  printf("Joe is at memory location %p:\n", &joe);
  Person_print(joe);

  printf("Tom is at memory location %p:\n", &tom);
  Person_print(tom);

  return 0;
}

