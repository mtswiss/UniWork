#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int main(void) {
  int a[SIZE], i;
  int *p;

  // Output all of the array values as we compute them:
  printf("[ ");
  for (i = 0; i < SIZE; ++i) {
    a[i] = rand() % 100;
    printf("%i ", a[i]);
  }
  printf("]\n");

  // Now output every second element as asked.
  p = &a[0];
  printf("a = [ ");
  for (i = 0; i < ((SIZE + 1) / 2); ++i) { // *SEE NOTE BELOW*
    printf("%i ", *p);
    p = p + 2; // <- Step 2 elements forward in array.
  }
  printf("]\n");

  return 0;
}

/****
 *
 * NOTE:
 *
 *   Why 'i < ((SIZE + 1) / 2)' as the loop condition? What happened to just
 * plain 'i < SIZE' ?
 *
 *   Our function pointer, 'p', is striding two steps forward through the
 * array on each iteration of the loop now. If we loop once for every element
 * of the array (as we did before) then we'll quickly run off the end of the
 * array. If we're striding twice as far we need to take only half as many
 * steps.
 *
 *   So why not 'i < SIZE / 2' ?
 *
 *   Consider a odd sized arrays, for instance one of size 3. How many
 * elements should we print out in this case? It should be 2: element 0 and
 * element 2. However 3 / 2 = 1 (in integer division), so our loop would
 * only run once, and we'd fail to print out element 2. Effectively what we
 * want is to "round up" rather than truncating our division. Since we're
 * dividing by two we can do this by adding one then rounding down, hence
 * 'i < ((SIZE + 1) / 2)'.
 *
 ****/
