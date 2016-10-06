#include <stdio.h>

int main(int argc, char *argv[]) 
{
  /* The Data */

  // Assign integer to variable `distance`.
  int distance       = 100;

  // Assign float to variable `power`.
  float power        = 2.345f;

  // Assign double to variable `super_power`.
  double super_power = 56789.4532;

  // Assign char to variable `initial`.
  char initial       = 'J';

  // Assign char array to variable `first_name`.
  char first_name[]  = "Pat";

  // Assign char array to variable `last_name`.
  char last_name[]   = "White";

  /* The Work */
  printf("You are %d miles away.\n", distance);
  printf("You have %f levels of power.\n", power);
  printf("You have %f awesome super powers.\n", super_power);

  printf("I have an initial %c.\n", initial - 1);
  printf("I have first name %s.\n", first_name + 1);
  printf("I have last name %s.\n", last_name - 1);
  printf("My whole name is %s %c. %s.\n",
      first_name, initial, last_name);

  /* More Data */

  // Assign integer to variable `bugs`.
  int bugs = 100;

  // Assign double to variable `bug_rate`.
  double bug_rate = 1.2;

  printf("You have %d bugs at the imaginary rate of %f.\n",
      bugs, bug_rate);

  // Assign long integer to variable `universe_of_defects`.
  long universe_of_defects = 1L * 1024L * 1024L * 1024L;
  printf("The entire universe has %ld bugs.\n", universe_of_defects);

  // Assign double to variable `expected_bugs`.
  double expected_bugs = bugs * bug_rate;
  printf("You are expected to have %f bugs.\n", expected_bugs);

  // Assign double to variable `part_of_universe`.
  double part_of_universe = expected_bugs / universe_of_defects;
  printf("That is only %e portion of the universe.\n", part_of_universe);

  /*  This makes no sense just a demo of something weird */
  
  // Assign char to variable `nul_byte`.
  char nul_byte = '\0';

  // Assign integer to variable `car_percentage`.
  int care_percentage = bugs * nul_byte;
  printf("Which means you should care %d%%.\n", care_percentage);


  return 0;
}
