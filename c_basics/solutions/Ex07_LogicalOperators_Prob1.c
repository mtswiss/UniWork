#include <stdio.h>

int main(void) {
  int n;
  printf("Enter an int: ");
  scanf("%i", &n);

  if (n % 2 == 0 || n < 10) {
    printf("You entered an EVEN number less, or less than 10.\n");
  } else {
    printf("You entered an ODD number greater than 9.\n");
  }

  return 0;
}
