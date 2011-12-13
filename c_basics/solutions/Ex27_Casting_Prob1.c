#include <stdio.h>

int main(void) {
  int a = 5, b = 3;
  float f;  

  f = a / b;
  printf("f is %f.\n", f);

  f = a / (float)b;
  printf("f is %f.\n", f);

  printf("f is %i.\n", (int)f);

  return 0;
}
