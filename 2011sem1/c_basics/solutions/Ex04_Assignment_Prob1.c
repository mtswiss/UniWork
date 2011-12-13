#include <stdio.h>

int main(void) {
  int n = 42;
  // The expression below is equivalent to 4n^3 + 7n^2 + 2n + 1

  n = (4 * n * n * n) + (7 * n * n) + (2 * n) + 1;

  printf("The value of n is %i.\n", n);
  return 0;
}
