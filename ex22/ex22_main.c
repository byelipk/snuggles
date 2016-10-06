#include "ex22.h"
#include "dbg.h"

const char *MY_NAME = "Zed A. Shaw";

void scope_demo(int count)
{
  log_info("count is %d\n", count);

  if (count > 10) {
    int count = 100;

    log_info("count in this scope is %d\n", count);
  }

  log_info("count at exit is %d\n", count);

  count = 3000;

  log_info("count after assign is %d\n", count);

  /* This will cause a seg fault due to a stack overflow */
  scope_demo(count);
}

int main(int argc, char *argv[])
{
  // test out THE_AGE accessors
  log_info("My name is %s, age: %d\n", MY_NAME, get_age());

  set_age(100);

  log_info("My age is now %d\n", get_age());

  // test out THE_SIZE extern
  log_info("THE_SIZE is %d\n", THE_SIZE);
  print_size();

  THE_SIZE = 9;

  log_info("THE_SIZE is now %d\n", THE_SIZE);
  print_size();


  // test the ratio function static
  log_info("Ratio at first: %f\n", update_ratio(2.0));
  log_info("Ratio again: %f\n", update_ratio(10.0));
  log_info("Ratio once more: %f\n", update_ratio(300.0));


  // test the scope demo
  int count = 4;
  scope_demo(count);
  scope_demo(count * 20);
  log_info("count after calling scope_demo is %d\n", count);

  printf("test screwing around with static function variable pointers\n");
  double *ptr = static_double_ptr();

  printf("Before...\n");
  printf("%p\n", ptr);
  printf("%f\n", *ptr);

  *ptr = 10.987;

  printf("After...\n");
  printf("%p\n", ptr);
  printf("%f\n", *ptr);
  printf("\n");

  printf("test screwing around with constant variable pointers\n");
  printf("Before...\n");
  printf("%p\n", MY_NAME);
  printf("%s\n", MY_NAME);
  printf("%c\n", MY_NAME[0]);

  char *point = (char *)&MY_NAME[0];


  printf("After...\n");
  printf("%p\n", point);
  printf("%c\n", *point);

  /* Causes a bus error */
  /* *point = 'P'; */

  printf("%s\n", MY_NAME);

  return 0;
}
