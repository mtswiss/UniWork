#include <stdio.h>

int main(void) {
  int n, m;
  printf("Enter two ints, separated by a space: ");
  scanf("%i", &n); // Two scanfs this time, instead of one with two
  scanf("%i", &m); // arguments. Just to add some variety. The effect
                   // is the same either way.

  if (n % 2 == 0) {
    if (m % 2 == 0) {
      printf("%i is EVEN and %i is EVEN.\n", n, m);
    } else {
      printf("%i is EVEN and %i is ODD.\n", n, m);
    }
  } else {
    if (m % 2 == 0) {
      printf("%i is ODD and %i is EVEN.\n", n, m);
    } else {
      printf("%i is ODD and %i is ODD.\n", n, m);
    }
  }

  return 0;
}
