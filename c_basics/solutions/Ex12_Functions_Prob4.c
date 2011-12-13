#include <stdio.h>

int factorial(int n) {
  int i, result = 1;

  for (i = 1; i <= n; ++i) {
    result = result * i;
  }

  return result;
}

void MyFunc(void) {
  int n, r;

  printf("Enter an int: ");
  scanf("%i", &n);

  r = factorial(n);

  printf("n! is %i\n", r);

  // NOTE: No 'return 0'. You can't return a value from a void function.
}

int main(void) {
  MyFunc();
  return 0;
}
