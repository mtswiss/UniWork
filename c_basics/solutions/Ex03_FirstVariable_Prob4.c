#include <stdio.h>

int main(void) {
  // Everything works just as well if we call the variable 'x', as
  // long as we're consistent.

  int x = 42;
  printf("The value of n is %i.\n", x);

  // Note that I've left "n" in the format string above, though the
  // variable is now called 'x'. This is just to emphasise that the
  // format string is freeform - you can write whatever you like
  // in there.

  return 0;
}
