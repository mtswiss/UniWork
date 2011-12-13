#include <stdio.h>

// Recursive Fibonacci (Warning: Not efficient! Ask in class for the reason).
//
// We can define the Fibonacci sequence recursively as
//
//                          f(n) = f(n - 1) + f(n - 2)
//
int fibonacci(int n) {
  if (n == 0) {
    return 0;
  } else if (n == 1) {
    return 1;
  } else {
    return fibonacci(n - 1) + fibonacci(n - 2);
  }
}

int main(void) {
  int n, r;

  printf("Enter an int: ");
  scanf("%i", &n);

  r = fibonacci(n);

  printf("fibonacci(n) is %i\n", r);

  return 0;
}

