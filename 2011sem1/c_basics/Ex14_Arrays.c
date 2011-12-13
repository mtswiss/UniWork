#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define ASIZE 10

int main(void) {
  assert(ASIZE > 0);

  int a[ASIZE], i; // Declare an array of size ASIZE

  // Initialise the array:
  for (i = 0; i < ASIZE; ++i) {
    a[i] = rand() % 100; // Random number from 0 - 99.
  }

  // Print out the array:
  printf("a = [ ");
  for (i = 0; i < ASIZE; ++i) {
    printf("%i ", a[i]);
  }
  printf("]\n");

  // Extract one element
  printf("Element number? ");
  scanf("%i", &i);
  printf("a[%i] = %i\n", i, a[i]);

  return 0;
}

/****
 *
 * Exercises:
 *
 * 1) Change the ASIZE macro to a different value (larger or smaller).
 *    What is the effect?
 *
 * 2) Write a loop to sum the random values in the array and print out
 *    the result.
 *
 */

