#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include "dbg.h"

#define MAX_LEN 1024

typedef int (*lib_function)(const char *data, size_t count);

int main(int argc, char *argv[])
{
  int rc = 0;
  check(argc == 4, "USAGE: ex29 libex29.so <function> <...data>");

  char *lib_file   = argv[1];
  char *fun_to_run = argv[2];
  char *data       = argv[3];

  size_t count = strnlen(data, MAX_LEN);

  void *lib = dlopen(lib_file, RTLD_NOW);
  check(lib != NULL, "Failed to open the library %s: %s", 
      lib_file, dlerror());

  lib_function func = dlsym(lib, fun_to_run);
  check(func != NULL, "Did not find %s function in the library %s: %s", 
      fun_to_run, lib_file, dlerror());

  rc = func(data, count);
  check(rc == 0, "Function %s returned %d for data: %s", 
      fun_to_run, rc, data);

  rc = dlclose(lib);
  check(rc == 0, "Failed to close %s", lib_file);

  return 0;

error:
  return -1;
}
