#include <stdio.h>

int main(void) {
  int n = 42;
  (n + 7) = 1; // Compiler error here.

  // The reason is that n+7 isn't a variable that can be assigned to.

  printf("The value of n is %i.\n", n);
  return 0;
}
