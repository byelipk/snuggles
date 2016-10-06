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


/* Declare a function called `Person_create` that returns a */
/* pointer to a struct of type Person */
struct Person *Person_create(char *name, int age, int height, int weight)
{
  /* Allocate enough bytes in memory to store a struct of `type Person`.
   * Assign that block of memory to a pointer of type `struct Person` 
   * called `who`. If there was a problem allocating that memory, `who`
   * would be equal to NULL. So we check to make sure that we have a
   * pointer that is not NULL. */
  struct Person *who = malloc(sizeof(struct Person));  
  assert(who != NULL);

  /* Use the structure dereference operator to assign all the elements 
   * that are of type `int`.*/
  who->age    = age;
  who->height = height;
  who->weight = weight;

  /* The function `strdup` makes a copy of the string. The idea behind
   * copying the string is that because the string comes from outside
   * the function, it may be needed in other places. The struct should
   * have it's own version of the string. This iscreases overhead a bit
   * because we'll need to remember to free the struct's copy of the string
   * when we destroy the struct. */
  who->name = strdup(name);

  return who;
}

void Person_destroy(struct Person *who) 
{
  assert(who != NULL);

  /* Let's give the OS back its memory */
  free(who->name);
  free(who);
}

void Person_print(struct Person *who)
{
  printf("Name: %s\n", who->name);
  printf("\tAge: %d\n", who->age);
  printf("\tHeight: %d\n", who->height);
  printf("\tWeight: %d\n", who->weight);
}

int main(int argc, char *argv[])
{
  // why is this 24 and not 20?
  printf("The size of a Person struct is %ld bytes.\n", sizeof(struct Person));

  // make two people structures
  struct Person *joe = Person_create("Joe Alex", 32, 63, 140);
  struct Person *tom = Person_create("Tom Blan", 20, 72, 180);

  // print them out and where they are in memory
  printf("Joe is at memory location %p:\n", joe);
  Person_print(joe);

  printf("Tom is at memory location %p:\n", tom);
  Person_print(tom);


  // destroy them both so we clean up
  Person_destroy(joe);
  Person_destroy(tom);

  return 0;
}

