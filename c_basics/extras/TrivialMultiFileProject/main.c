#include <stdio.h>

#include "unit1.h"

int main(void) {
  int f = foo();
  printf("foo returned %i.\n", f);
  return 0;
}
