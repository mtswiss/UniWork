#include <stdio.h>

int main(void) {
  int n, i;

  printf("Enter an int: ");
  scanf("%i", &n);

  // Initialize with i = n, test i < n immediately, this loop will
  // never execute.

  for (i = n; i < n; ++i) {
    printf("%i\n", i);
  }

  // Initialize with i = n, test i < n after the first iteration, this
  // loop will always execute exactly once.

  i = n;
  do {
    printf("%i\n", i);
    i = i + 1;
  } while (i < n);

  return 0;
}
