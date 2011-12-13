#include <stdio.h>

// factorial is a new C function.
// It takes one integer parameter (n), and returns an integer result.
int factorial(int n) {
  int i, result = 1;

  for (i = 1; i <= n; ++i) {
    result = result * i;
  }

  return result;
}

int MyFunc(void) {
  int n, r;

  printf("Enter an int: ");
  scanf("%i", &n);

  r = factorial(n);

  printf("n! is %i\n", r);

  return 0;
}

int main(void) {
  MyFunc();
  return 0;
}
