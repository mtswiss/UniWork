#include <stdio.h>

int main(void) {
  int n;
  printf("Enter an int: ");
  scanf("%i", &n);

  // Note: You'll need to swap the body of the 'if' and the 'else' for the
  // output to make sense again.

  if ( ! (n % 2 == 0 && n < 10)) { // Whole condition negated.
    printf("You entered an EVEN number less than 10.\n"); // False.
  } else {
    printf("You entered an ODD number, or greater than 9.\n"); // False.
  }

  return 0;
}
