#include <stdio.h>
#include "ex22.h"
#include "dbg.h"

int THE_SIZE = 100;

// When the static keyword is used at the file level (i.e. outside a function)
// it has the reverse effect of the extern keyword.
//
// Here it means THE_AGE is only used in this .c file and should not be
// available to other parts of the program. 
static int THE_AGE = 37;

int get_age()
{
  return THE_AGE;
}

void set_age(int age)
{
  THE_AGE = age;
}

double update_ratio(double new_ratio)
{
  // When you declare a variable inside a function static, it has the
  // effect of defining the variable outside the function with the
  // caveat that only this function can access the static variable.
  //
  // It's a way of creating static state inside a function. It's similar
  // to mutable data that lives inside a class in OO languages.
  static double ratio = 1.0;

  double old_ratio = ratio;

  ratio = new_ratio;

  return old_ratio;
}

double *static_double_ptr()
{
  static double ratio = 1.0;

  return &ratio;
}

void print_size()
{
  log_info("I think the size is %d\n", THE_SIZE);
}
