#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define ASIZE 10

int main(void) {
  assert(ASIZE > 0);

  int a[ASIZE], i, sum;

  for (i = 0; i < ASIZE; ++i) {
    a[i] = rand() % 100; // Random number from 0 - 99.
  }

  printf("a = [ ");
  for (i = 0; i < ASIZE; ++i) {
    printf("%i ", a[i]);
  }
  printf("]\n");

  // Sum the values in the array.
  sum = 0;
  for (i = 0; i < ASIZE; ++i) {
    sum = sum + a[i];
  }
  printf("sum of array values is %i.\n", sum);

  return 0;
}
