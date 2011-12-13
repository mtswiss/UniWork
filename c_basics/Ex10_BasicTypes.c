#include <stdio.h>

int main(void) {

  int n = -10; // An integer.
  char c = 'A'; // A character.
  float f = -3.5; // A single-precision floating point number.
  double d = -3.5; // A double-precision floating point number.
  char *s = "A string!"; // A character string.

  printf("n is %i, c is %c\n", n, c); // %i for integers, %c for chars.
  printf("f is %f, d is %f\n", f, d); // %f for both floats and doubles.
  printf("s is %s\n", s); // %s for strings.

  return 0;
}

/****
 *
 * Exercises:
 *
 * 1) Modify this program to alter the initial values of the variables
 *    before printing them (use assignment statements).
 *
 * 2) What happens if you mix up the types of the format string identifiers
 *    with those of the arguments to printf? E.g. try to print a float with
 *    %i, or an int with %f?
 *
 */
