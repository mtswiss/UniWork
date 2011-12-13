#include <stdio.h>

int main(void) {
  int i, num, hi, lo, tmp;

  scanf("%d", &num);

  printf("1 ");
  lo = 0;
  hi = 1;
  for (i = 1; i <= num; ++i) {
    tmp = hi + lo;
    printf("%d ", tmp);
    lo = hi;
    hi = tmp;
  }

  printf("\n");
  return 0;
}
