#include <stdio.h>


/* Helper method */
void message(char *string, int n)
{
  printf("%s has %d years alive.\n", string, n);
}



/* METHOD ONE - simple indexing */
void method_one(char **chars, int *ints, int count)
{
  int i = 0;

  for (i = 0; i < count; i++) {
    message(chars[i], ints[i]);
  }
}



/* METHOD TWO - pointer arithmetic */
void method_two(char **chars, int *ints, int count)
{
  // setup the pointers to the start of the arrays
  int *cur_age     = ints;
  char **cur_name  = chars;

  int i = 0;

  for (i = 0; i < count; i++) {
    /* We read this syntax as: */
      /* "the value of (pointer cur_name plus i)" */
      /* "the value of (pointer cur_age  plus i)" */
    message(*(cur_name + i), *(cur_age + i));
  }
}



/* METHOD THREE - pointers are arrays */
void method_three(char **chars, int *ints, int count)
{
  // setup the pointers to the start of the arrays
  int *cur_age     = ints;
  char **cur_name  = chars;

  int i = 0;

  for (i = 0; i < count; i++) {
    message(cur_name[i], cur_age[i]);
  }
}



/* METHOD FOUR - crazyness */
void method_four(char **chars, int *ints, int count)
{
  // setup the pointers to the start of the arrays
  int *cur_age;     
  char **cur_name; 


  for(cur_age = ints, cur_name = chars; 
      (cur_age - ints) < count; 
      cur_age++, cur_name++) {

    /* NOTE */
    /* In the incrementer we're telling `cur_age` to increment  */
    /* itself by 4 bytes, the size of an int, at the completion */
    /* of each iteration. */
    message(*cur_name, *cur_age);

  }
}

int main(int argc, char *argv[])
{
  // create two arrays we care about
  int ages[]    = { 23, 43, 12, 89, 2 };
  char *names[] = { "Alan", "Frank", "Mary", "John", "Lisa" };

  // safely get the sizes of ages
  int count = sizeof(ages) / sizeof(int);

  // first way using indexing
  method_one(names, ages, count);

  printf("---\n");

  // second way using pointers
  method_two(names, ages, count);

  printf("---\n");


  // third way, pointers are just arrays
  method_three(names, ages, count);


  printf("---\n");

  // fourth way, crazyness
  method_four(names, ages, count);


  /* A pointer is a variable whose value is a memory address. */


  return 0;
}
