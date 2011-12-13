#include <stdio.h>

int main(void) {
  int n;
  printf("Enter an int: ");
  scanf("%i", &n);

  if (n % 2 == 0) { // % is the modulo operator.
    printf("You entered an EVEN number.\n");
  } else {
    printf("You entered an ODD number.\n");
  }

  return 0;
}

/****
 *
 * Note:
 *
 *   In the if test we use '==' to test equality, rather than '='.
 * In C '==' is always used to test equality, and '=' is reserved
 * for assignment.
 *
 *   '==' is a "relational operator. It tests a relationship between
 * two quantities. The other relational operators in C are:
 *
 *                      '!='  - inequality
 *                      '<'   - less than
 *                      '>'   - greater than
 *                      '<='  - less than or equal to
 *                      '>='  - greater than or equal to
 *
 * Exercises:
 *
 * 1) Try altering the condition to test other properties besides
 *    odd/even-ness. Can you test divisibility by some other number?
 *
 * 2) Try adding a second variable 'm' and reading a value for it (leave the
 *    original read for 'n' in place). Change the if test to compare the two
 *    values that are entered for some property. E.g. (n < m).
 *
 * 3) Can you compare more complex expressions with the relational operators,
 *    such as (2 * n + 1 == m) ?
 *
 * 4) Can you "nest" if tests to test multiple conditions? (E.g. test even-ness
 *    and then, if the number is even, test that it is less than 10 by placing
 *    a 2nd 'if' inside the first?)
 *
 * 5) Try dropping the parentheses around the condition. What happens?
 *
 * 6) What happens if you drop the else clause (including the code
 *    in braces following the else keyword)? Does the program still
 *    work? If so, what happens when the condition fails?
 *
 ****/
