#include <stdio.h>

int main(void) {
  int n, i = 0; // i will be our index variable.
  int prev, cur = 1, next = 1;

  printf("Enter an int: ");
  scanf("%i", &n);

  // This is easy. Printing the "nth" number only just means not printing
  // the numbers before it. So our first step is to delete the print statement
  // from the loop.

  // Second thing to notice is that each iteration through the loop updates
  // "cur" to the next value in the sequence. Since we start on the first
  // number we want to run the loop zero times for the first Fibonacci,
  // one time for the second and so on. So we need to subtract 1 from the
  // right hand side of our condition.

  while (i < n - 1) {

    // printf("...");   // <- We used to print here.

    prev = cur; // Back up "cur" as "prev"
    cur = next; // Move the "next" Fibonacci number into "cur".
    next = cur + prev; // Calculate new "next" using the previous two vals.

    i = i + 1; // Increment our loop index.
  }

  // Now we can print here, after the loop:
  printf("The %ith Fibonacci number is %i.\n", n, cur);

  return 0;
}
