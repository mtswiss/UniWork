// stdio.h also gives us access to the scanf function which reads input.
#include <stdio.h>

int main(void) {
  int n;
  printf("Enter an int: "); // <- Note the lack of '\n': no newline.
  scanf("%i", &n); // <- Note the ampersand (&). No '\n' in here either.
  printf("You entered the int %i.\n", n);
  return 0;
}

/****
 *
 * An important note:
 *
 *   In the call to scanf the & operator before the n variable is crucial.
 * (What happens when you take it out? Try this out!).
 *
 *   Conversly you never want to put the & operator before an operator to
 * printf.
 *
 *   For now we will just take this as a Law of C: scanf arguments have
 * ampersands in front of them, printf arguments do not. Later in the
 * course you will learn the reason for this seemingly odd asymmetry
 * between the printf and scanf arguments (as well as some exceptions to
 * the 'Laws' described above).
 *
 * Exercises:
 *
 * 1) As suggested above: Try removing the & from the scanf call? What
 *    happens? What happens if you add an ampersand to the n parameter of
 *    the 2nd printf call?
 *
 * 2) Can you combine what we learned about assignments to print out an
 *    expression based on the value the user inputs, rather than just
 *    echoing the value?
 *
 ****/
