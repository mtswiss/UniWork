#include <stdio.h>

// This function takes an integer parameter. Because C uses pass-by-value for
// basic types this function can modify its parameter, but not the variable
// which was passed as an argument.
void cannot_modify(int x) {
  printf("cannot_modify passed x = %i\n", x);
  x = 7; // Legal, but effects 'x' only for the duration of the function.
  printf("cannot_modify terminating with x = %i\n", x);
}

// This function takes a pointer to an integer. Through this pointer it can
// both access and modify the variable passed as argument.
void can_modify(int* x) {
  printf("can_modify passed x = %i\n", *x);
  *x = 7; // Modifies original argument in caller.
  printf("can_modify terminating with x = %i\n", *x);
}

int main(void) {
  int y = 1;
  printf("In main (initially): y = %i\n", y);
  cannot_modify(y);
  printf("In main (after cannot_modify(y)): y = %i\n", y);
  can_modify(&y); // Note: Must pass y's address using '&'.
  printf("In main (after can_modify(y)): y = %i\n", y);
  return 0;
}

/****
 *
 * Exercises:
 *
 * 1) Write a 'swap' function which swaps the values of its arguments.
 *
 *     E.g. if x = 7 and y = 10, then after
 *
 *            swap(&x, &y);
 *
 *          x = 10 and y = 7.
 *
 */
