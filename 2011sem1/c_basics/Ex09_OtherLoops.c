#include <stdio.h>

int main(void) {
  int n, i;

  printf("Enter an int: ");
  scanf("%i", &n);

  // The following loop behaves the same as the 'while' loop
  // from the previous exercise, but it gathers initialization
  // condition checking, and index increment into one place.
  // The way to read a for loop is:
  //
  // for (<initialisation>; <condition>; <increment>) {
  //   <loop body>
  // }
  //
  // 'for' loops appear very frequently in "real world" C code.

  for (i = 0; i < n; ++i) {
    printf("%i\n", i);
  }

  // This next loop does not, in general, behave the same as
  // the while loop, even though it looks very similar.
  // This 'do' loop is an "unguarded" loop. Control will always pass
  // through it at least once, regardless of whether the loop
  // condition is satisfied.
  // 'do' loops are rare in "real world" C code, and you should
  // use the 'while' variant wherever possible.

  i = 0;
  do {
    printf("%i\n", i);
    i = i + 1;
  } while (i < n);

  return 0;
}

/****
 *
 * Exercises:
 *
 * 1) Try changing the initialization of each loop so that the
 *    loop condition is never true to begin with. E.g. Initialize
 *    i to n. What happens to the behaviour of the 'for' loop?
 *    What happens to the 'while' loop?
 *
 * 2) Try to write a for loop which computes the factorial of a
 *    number entered by the user. Remember: The factorial of 'n',
 *    written n!, is
 *
 *          n * (n - 1) * (n - 2) * ... * 3 * 2 * 1
 *
 *    and the factorial of 0 is 1 (i.e. 0! = 1)
 *
 ****/
