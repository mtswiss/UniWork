#include "unit1.h"

#include <stdio.h>

int foo(void) {
  int r = 42;
  printf("foo() called. Returning %i.\n", r);
  return r;
}
