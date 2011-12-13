#include <stdio.h>

int main(void) {
  int n, i = 0, j;

  printf("Enter an int: ");
  scanf("%i", &n);

  while (i < n) {
    j = 0; // Need to run this each time we go through the outer loop.
    while (j < n) {
      printf("%i%i ", i, j);
      j = j + 1; // Increment our inner loop counter.
    }
    i = i + 1; // Increment our outer loop counter.
  }

  printf("\n"); // Add a newline for tidy output.

  return 0;
}
