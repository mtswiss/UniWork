#include <stdio.h>

int main(void) {
  int a, b; // 'a' and 'b' declared but uninitialised.
  int* p;
  int* q;

  p = &a; // 'p' pointed at 'a'.
  q = &b; // 'q' pointed at 'b'.

  *p = 7; // Initialised 'a' by dereferencing 'p' and storing 7 in it.
  *q = 8; // Initialised 'b' by dereferencing 'q' and storing 8 in it.

  *p = *p + *q; // Effectively adds 'a' and 'b' and stores the result in 'a'.
  *q = 2 * (*p); // Store 2 * 'a' in 'b'.

  // We would now expect 'a' to be 15, and 'b' to be 30.
  printf("a = %i, b = %i\n", a, b);

  return 0;
}
