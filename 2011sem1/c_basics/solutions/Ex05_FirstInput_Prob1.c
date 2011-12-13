#include <stdio.h>

int main(void) {
  int n;
  printf("Enter an int: ");
  scanf("%i", n); // BAD! BAD! BAD!

  // No ampersand on the scanf parameter. This program will most likely
  // crash with a 'Segmentation Fault' when input is entered.

  printf("You entered the int %i.\n", n);
  return 0;
}
