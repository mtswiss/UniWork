#include <stdio.h>

int main(void) {
  int n, m;
  printf("Enter two ints, separated by a space: ");
  scanf("%i %i", &n, &m);

  if (n < m) {
    printf("%i is less than %i.\n", n, m);
  } else {
    printf("%i is not less than %i.\n", n, m);
  }

  return 0;
}
