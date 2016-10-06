#include <stdio.h>
#include "dbg.h"

#define MAX_DATA 100

typedef enum EyeColor {
  BLUE_EYES, GREEN_EYES, BROWN_EYES, BLACK_EYES, OTHER_EYES
} EyeColor;

const char *EYE_COLOR_NAMES[] = {
  "Blue", "Green", "Brown", "Black", "Other"
};

typedef struct Person {
  int age;
  char first_name[MAX_DATA];
  char last_name[MAX_DATA];
  EyeColor eyes;
  float income;
} Person;

int main(int argc, char *argv[])
{

  /* Our Person sturct */
  Person you = { .age = 0 };

  /* This will be our input buffer. We'll read into this from stdin. */
  char *in = NULL;

  printf("What's your first name? ");

  /* fgets will read MAX_DATA - 1 bytes from the stdin stream 
   * and copy it over into you.first_name */
  in = fgets(you.first_name, MAX_DATA, stdin);
  check(in != NULL, "Failed to read first name.");

  printf("What's your last name? ");
  in = fgets(you.last_name, MAX_DATA, stdin);
  check(in != NULL, "Failed to read last name.");

  printf("How old are you? ");
  fscanf(stdin, "%d", &you.age);
  check(in != NULL, "Failed to read age.");

  printf("What color are your eyes:\n");
  for (int i = 0; i <= OTHER_EYES; i++) {
    printf("%d) %s\n", i + 1, EYE_COLOR_NAMES[i]);
  }

  printf("> ");

  int eyes = -1;
  int rc   = fscanf(stdin, "%d", &eyes);
  check(rc > 0, "You have to enter a number.");

  you.eyes = eyes - 1;
  check(you.eyes <= OTHER_EYES && you.eyes > 0, 
      "Do it right, that's not an option.");

  printf("How much do you make an hour? ");
  rc = fscanf(stdin, "%f", &you.income);
  check(rc > 0, "Enter a floating point number.");

  printf("----- RESULTS -----\n");

  printf("First Name: %s", you.first_name);
  printf("Last Name: %s", you.last_name);
  printf("Age: %d\n", you.age);
  printf("Eyes: %s\n", EYE_COLOR_NAMES[you.eyes]);
  printf("Income: %f\n", you.income);

  return 0;
error:

  return -1;
}
