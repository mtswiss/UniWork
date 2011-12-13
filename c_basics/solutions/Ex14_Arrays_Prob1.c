#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define ASIZE 15

int main(void) {
  assert(ASIZE > 0);

  int a[ASIZE], i;

  for (i = 0; i < ASIZE; ++i) {
    a[i] = rand() % 100;
  }

  printf("a = [ ");
  for (i = 0; i < ASIZE; ++i) {
    printf("%i ", a[i]);
  }
  printf("]\n");

  printf("Element number? ");
  scanf("%i", &i);
  printf("a[%i] = %i\n", i, a[i]);

  return 0;
}
