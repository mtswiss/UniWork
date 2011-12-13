#include <stdio.h>

int main(void) {
  int i, num, hi, lo;

  scanf("%d", &num);

  if (num < 1) 
    return -1;

  printf("1 ");
  lo = 0;
  hi = 1;
  for (i = 1; i < num; i++) {
    printf("%d ", hi + lo);
    lo = hi;
    hi = hi + lo;
  }

  printf("\n");
  return 0;
}
