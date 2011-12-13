#include <stdio.h>

int main(void) {
  int n = 42;

  // Two format string identifiers (%i) means we need two arguments after
  // the format string, i.e. ', n, n'.

  printf("Printing n once, %i, twice, %i.\n", n, n);
  return 0;
}
