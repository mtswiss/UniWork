// The stdio.h header declares printf, among other functions.
#include <stdio.h>

int main(void) {
  printf("Hello, World!\n"); // Anything encased in double quotes is a
                             // "string literal".
  return 0;
}

/****
 *
 * Exercises:
 *
 * 1) Alter this program to print something different, like your name.
 *
 * 2) Try removing the trailing '\n' from the string literal. What is the
 *    effect?
 *
 * 3) What happens if you add additional printf calls? In what order
 *    are they executed?
 *
 * 4) Try adding, removing or altering some comments. What happens to the
 *    program's behaviour?
 *
 ****/
