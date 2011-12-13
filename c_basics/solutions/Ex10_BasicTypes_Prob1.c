#include <stdio.h>

int main(void) {

  int n = -10;
  char c = 'A';
  float f = -3.5;
  double d = -3.5;
  char *s = "A string!";

  n = -100;
  c = 'Q';
  f = 3.141592;
  d = 2.718282;
  s = "Though this be madness, yet there is method in't.";

  printf("n is %i, c is %c\n", n, c);
  printf("f is %f, d is %f\n", f, d);
  printf("s is %s\n", s);

  return 0;
}
