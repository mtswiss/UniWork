#include <stdio.h>

int main(void) {
  int n = 42;
  n = n * 2 + 1; // Here we alter the value stored in n.
  printf("The value of n is %i.\n", n);
  return 0;
}

/****
 *
 * Exercises:
 *
 * 1) Try changing the expression on the RHS (right hand side) of the
 *    assignment. Can you get the program to print the square of the
 *    initial value? What about the cube? What about the negation?
 *
 * 2) What happens if you try to put a more complex expression like
 *    (n + 7) on the left hand side of the assignment? Does the
 *    code still compile? What does this tell you about the nature
 *    of the C assignment operator?
 *
 ****/
