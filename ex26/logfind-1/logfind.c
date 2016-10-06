#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dbg.h"

int main(int argc, char *argv[])
{
  check(argc > 1, "USAGE: logfind word word word");

  return 0;
error:
  return 1;
}
