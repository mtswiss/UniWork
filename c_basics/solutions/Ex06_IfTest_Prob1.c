#include <stdio.h>

int main(void) {
  int n;
  printf("Enter an int: ");
  scanf("%i", &n);

  if (n % 5 == 0) { // % is the modulo operator.
    printf("%i is evenly divisible by 5.\n", n);
  } else {
    printf("%i is not evenly divisible by 5.\n", n);
  }

  return 0;
}

