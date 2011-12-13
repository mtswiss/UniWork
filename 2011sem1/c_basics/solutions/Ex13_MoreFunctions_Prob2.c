#include <stdio.h>

unsigned int factorial1(unsigned int n) {
  unsigned int i, result = 1;

  for (i = 1; i <= n; ++i) {
    result = result * i;
  }

  return result;
}

unsigned int factorial2(unsigned int n) {
  unsigned int r;

  if (n == 0) {
    r = 1;
  } else {
    r =  n * factorial2(n - 1);
  }

  return r;
}

int main(void) {
  unsigned int n, r;

  printf("Enter an int: ");
  scanf("%u", &n);

  r = factorial2(n);

  printf("n! is %u\n", r);

  return 0;
}
