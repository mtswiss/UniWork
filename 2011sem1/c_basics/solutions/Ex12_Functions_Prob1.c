#include <stdio.h>

int square(int n) {
  return n * n;
}

int main(void) {
  int n, r;

  printf("Enter an int: ");
  scanf("%i", &n);

  r = square(n);

  printf("n squared is %i\n", r);

  return 0;
}
