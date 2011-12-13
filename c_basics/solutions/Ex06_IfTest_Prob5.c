#include <stdio.h>

int main(void) {
  int n;
  printf("Enter an int: ");
  scanf("%i", &n);

  if n % 2 == 0 { // COMPILER ERROR HERE: Conditions need parentheses.
                  // See previous Ex6 solutions for contrast with this error.
    printf("You entered an EVEN number.\n");
  } else {
    printf("You entered an ODD number.\n");
  }

  return 0;
}

