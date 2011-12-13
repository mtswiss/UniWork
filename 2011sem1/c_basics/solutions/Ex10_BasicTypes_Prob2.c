#include <stdio.h>

int main(void) {

  int n = -10;
  char c = 'A';
  float f = -3.5;
  double d = -3.5;
  char *s = "A string!";

  printf("n is %c, c is %i\n", n, c);
  printf("f is %i, d is %i\n", f, d);
  printf("s is %f\n", s);

  return 0;
}
