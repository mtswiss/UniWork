#include <stdio.h>

int main(void) {
  int a, b;
  printf("Enter two ints, separated by a space: ");
  scanf("%i %i", &a, &b);
  printf("The sum of %i + %i is %i.\n", a, b, a + b);
  return 0;
}
