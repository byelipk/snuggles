#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  int numbers[4] = { 0 };
  char name[4] = { 'a', 'a', 'a', 'a' };

  // first, print them out raw
  printf("numbers: %d %d %d %d\n",
      numbers[0], numbers[1], numbers[2], numbers[3]);

  printf("name each: %c %c %c %c\n",
      name[0], name[1], name[2], name[3]);

  printf("name: %s\n", name);


  // setup the numbers
  numbers[0] = 1;
  numbers[1] = 2;
  numbers[2] = 3;
  numbers[3] = 4;

  // setup the name
  name[0] = 'Z';
  name[1] = 'e';
  name[2] = 'd';
  name[3] = 'A';

  // then print them out initialized
  printf("numbers: %d %d %d %d\n",
      numbers[0], numbers[1], numbers[2], numbers[3]);

  printf("name each: %c %c %c %c\n",
      name[0], name[1], name[2], name[3]);

  // print the name like a string
  printf("name: %s\n", name);

  // another way to use
  char *another = "Zed";

  printf("another: %s\n", another);

  printf("another each: %c %c %c %c\n",
      another[0], another[1], another[2], another[3]);

  // crazy hack
  char *stuff = "Pat";
  int integers[4] = {1,2,3,4};

  memcpy(&integers, &stuff, 4);
  /* memcpy(stuff, &integers, 4); */

  printf("integers: %d %d %d %d\n",
      integers[0], integers[1], integers[2], integers[3]);

  printf("stuff each: %c %c %c %c\n",
      stuff[0], stuff[1], stuff[2], stuff[3]);





  return 0;
}
