#ifndef _ex22_h
#define _ex22_h

// makes THE_SIZE in ex22.c available to other .c files
//
// This keyword tells the compiler this variable will be 
// used in an "external" location. Usually that means it
// will be used in another .c file.
//
// By including this header file, ex22.c will have access
// to this variable.
extern int THE_SIZE;

// gets and sets an internal static variable in ex22.c
int get_age();
void set_age(int age);

// updates a static variable that's inside update_ratio()
double update_ratio(double ratio);

// Returns a pointer to a double
double *static_double_ptr();

void print_size();

#endif
