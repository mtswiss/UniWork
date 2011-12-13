#include <stdio.h>

int main(void) {
  int a, b;
  int* p;  // In a variable declaration, '*' indicates that 'p' is a pointer.
           // In this case of type pointer-to-int.

  a = 7;
  b = 32;

  printf("Variable 'a' has value %i.\n", a);
  printf("Variable 'b' has value %i.\n", b);

  p = &a; // Point 'p' at 'a'. '&' is the "address-of" operator, and after
          // this statement is run 'p' will contain the address of 'a'.

  printf("'p' pointed at 'a'.\n");
  printf("The address of 'a' is %p.\n", (void*)p);

  // In this context '*' is the "dereference" operator. It fetches the value
  // stored at the address pointed to by the pointer. Since 'p' currently
  // points to 'a', this will give the value contained in a.
  printf("The contents of 'a' is %i.\n", *p);

  printf("Adding 5 to 'a' via pointer 'p'.\n");

  *p = *p + 5;

  printf("Now 'a' has value %i.\n", a);

  p = &b;
  printf("'p' pointed at 'b'.\n");
  printf("The address of 'b' is %p.\n", (void*)p);
  printf("The contents of 'b' is %i.\n", *p);
  printf("Adding 5 to 'b' via pointer 'p'.\n");

  *p = *p + 5;

  printf("Now 'b' has value %i.\n", b);

  return 0;
}

/****
 *
 * Exercises:
 *
 * 1) Write a new program with two integer variables, a and b, both initialized
 *    to zero, and two pointers p and q pointed at a and b respectively. Have
 *    the program initialise a and b, and calculate some expression involving
 *    them, without ever referencing a and b in the expressions. I.e. you 
 *    should use pointer dereference on p and q to access a and b.
 *
 *    At the end of your program print out the value of 'a' and 'b' to confirm
 *    that it matches your expectation.
 *
 */
