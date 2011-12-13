#include <stdio.h>

int main(void) {
  int n, i, f;

  printf("Enter an int: ");
  scanf("%i", &n);

  // The factorial of a number n, written n!, is
  // n * (n - 1) * (n - 2) * ... * 3 * 2 * 1
  //
  // By convention, 0! = 1.
  //
  // 'f' will be our "accumulator", which accumulates the value we
  // want to compute. We begin by assigning 1 to 'f'. We then loop for
  // each value in the range [2..n], multiplying our accumulator by
  // i each time. If n < 2 obviously this range is empty, and the loop
  // never executes.
  //
  // So the first iterations around the loop give (with the loop index
  // shown on the left) give:
  //
  // 2) f = i * f     which is    f = 2 * 1     which is    f = 2
  // 3) f = i * f     which is    f = 3 * 2     which is    f = 6
  // 4) f = i * f     which is    f = 4 * 6     which is    f = 24
  // 5) f = i * f     which is    f = 5 * 24    which is    f = 120
  //
  // And so on...

  f = 1;
  for (i = 2; i <= n; ++i) {
    f = i * f;
  }

  // At the end our accumulator contains the value we want.
  printf("%i! is %i.\n", n, f);

  return 0;
}
