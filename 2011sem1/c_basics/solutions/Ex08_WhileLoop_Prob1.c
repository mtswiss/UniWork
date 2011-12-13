#include <stdio.h>

int main(void) {
  int n, i = 0; // i will be our index variable.
  int prev, cur = 1, next = 1;

  printf("Enter an int: ");
  scanf("%i", &n);

  printf("The first %i Fibonacci numbers are:\n", n);

  while (i < n) {
    printf("%i\n", cur);

    prev = cur; // Back up "cur" as "prev"
    cur = next; // Move the "next" Fibonacci number into "cur".
    next = cur + prev; // Calculate new "next" using the previous two vals.

    i = i + 1; // Increment our loop index.
  }

  return 0;
}
