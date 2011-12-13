#include <stdio.h>

// Try '12'

int main(void) {
  int n;
  printf("Enter an int: ");
  scanf("%i", &n);

  if (n % 2 == 0 && n < 10) {
    printf("Condition with && (AND) PASSES.\n");
  } else {
    printf("Condition with && (AND) FAILS.\n");
  }

  if (n % 2 == 0 || n < 10) {
    printf("Condition with || (OR) PASSES.\n");
  } else {
    printf("Condition with || (OR) FAILS.\n");
  }

  printf("\n");
  printf("Can you find an input for which OR passes but AND fails?\n");
  printf("Hint: Try a number greater than 9.\n");

  printf("\n");
  printf("Can you find an input for which AND passes but OR fails?\n");
  printf("Why not? (Hint: It's a consequence of pure logic.)\n");

  return 0;
}
