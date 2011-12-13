#include <stdio.h>

int main(void) {
  int n;
  printf("Enter an int: ");
  scanf("%i", &n);

  if (n % 2 == 0 && n < 10) {
    printf("You entered an EVEN number less than 10.\n");
  } else {
    printf("You entered an ODD number, or greater than 9.\n");
  }

  return 0;
}

/****
 *
 * Note:
 *
 *   In C the '&&' operator represents the logical AND operation. It evaluates
 * to true if and only if each side of the operator evaluates to true.
 *
 *   The other basic logical operators are OR, represented by '||', and NOT,
 * represented by '!'.
 *
 * Exercises:
 *
 * 1) Try changing the AND operator to an OR operator. Since this changes the
 *    meaning of the condition you'll want to change the string literals. Make
 *    the new ones something generic like "The condition is TRUE" and
 *    "The condition is FALSE".
 *
 * 2) Find a value for which the condition with AND failed, but the new
 *    condition with OR passes.
 *
 * 3) Try negating the condition with NOT. What happens to your output when you
 *    enter the same values you tried previously?
 *
 ****/
