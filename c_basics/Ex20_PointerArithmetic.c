#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int main(void) {
  int a[SIZE], i;
  int *p;

  // Initialise the array with random values.
  for (i = 0; i < SIZE; ++i) {
    a[i] = rand() % 100;
  }

  // Print out the array using array access:
  printf("a = [ ");
  for (i = 0; i < SIZE; ++i) {
    printf("%i ", a[i]);
  }
  printf("]\n");

  // Print out the array using pointer dereference and arithmetic:
  p = &a[0];
  printf("a = [ ");
  for (i = 0; i < SIZE; ++i) {
    printf("%i ", *p); // <- Pointer dereference to access array element.
    p = p + 1; // <- Pointer arithmetic to point p at next array element.
  }
  printf("]\n");

  return 0;
}

/****
 *
 * Exercises:
 *
 * 1) Modify the second loop to print out only every 2nd array element using
 *    pointer arithmetic. Remember to change the loop condition or increment
 *    appropriately.
 *
 */
