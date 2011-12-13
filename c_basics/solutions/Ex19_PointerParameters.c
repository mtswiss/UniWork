#include <stdio.h>

void swap(int* a, int* b) {
  int t;
  t = *a;
  *a = *b;
  *b = t;
}

// Note: The 'swap' function above only works because 'a' and 'b' are pointers,
//       and we swap the things they point to. If 'a' and 'b' were plain int
//       parameters and we swapped their values the effect would be invisible
//       in the caller because of C's pass-by-value scheme.

int main(void) {
  int x = 1, y = 2;
  printf("x = %i, y = %i\n", x, y);
  swap(&x, &y);
  printf("x = %i, y = %i\n", x, y);
  return 0;
}
