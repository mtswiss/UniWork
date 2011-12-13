#include <stdio.h>

/*
** Fibonacci calculation program:
**    input - a single positive integer, num, where we assume this can 
**            be held as an int on this machine
**    output - the num-th Fibonnaci number
** by John Gibonnaci, Aug 10, 2000
*/

int main(void) {
  int i, num, hi, lo, tmp;

  scanf("%d", &num);

  if (num < 1) 
    return -1;

     /* inialisations */
     printf("1 ");
     lo = 0;
     hi = 1;
  for (i = 1; i < num; i++) {
    tmp = hi + lo;
    printf("%d ", tmp); /* print the next Fibonacci number */
    lo = hi;
    hi = tmp;
  }

  printf("\n");
  return 0;
}
