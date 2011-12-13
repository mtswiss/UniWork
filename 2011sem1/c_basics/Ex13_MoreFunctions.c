#include <stdio.h>

// Iterative factorial implementation
int factorial1(int n) {
  int i, result = 1;

  for (i = 1; i <= n; ++i) {
    result = result * i;
  }

  return result;
}

// Recursive factorial implementation.
int factorial2(int n) {
  int r;

  if (n == 0) {
    r = 1;
  } else {
    r =  n * factorial2(n - 1);
  }

  return r;
}

int main(void) {
  int n, r;

  printf("Enter an int: ");
  scanf("%i", &n);

  r = factorial2(n);

  printf("n! is %i\n", r);

  return 0;
}

/****
 *
 * Exercises:
 *
 * 1) Write (and test) recursive implementations of other recursive functions.
 *
 * 2) The factorial function isn't defined for negative integers, and it would
 *    be helpful if the type of our function reflected this. Change the return
 *    and parameter type of the 'factorial1' and 'factorial2' functions, using
 *    what you have learned about signed-ness of integer types in C.
 *
 ****/
