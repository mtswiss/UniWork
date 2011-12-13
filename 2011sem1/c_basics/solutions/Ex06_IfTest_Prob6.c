#include <stdio.h>

int main(void) {
  int n;
  printf("Enter an int: ");
  scanf("%i", &n);

  if (n % 2 == 0) { // % is the modulo operator.
    printf("You entered an EVEN number.\n");
  }

  // No else clause above, but the program still runs. If
  // you enter an odd number you just skip the 'if' block
  // and proceed straight to the return.

  return 0;
}

