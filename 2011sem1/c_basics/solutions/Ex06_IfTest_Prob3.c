#include <stdio.h>

int main(void) {
  int n;
  printf("Enter an int: ");
  scanf("%i", &n);

  if (2 * n + 1 > 15) {
    printf("2 * %i + 1 is greater than 15.\n", n);
  } else {
    printf("2 * %i + 1 is not greater than 15.\n", n);
  }

  return 0;
}
