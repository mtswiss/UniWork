#include <stdio.h>

int main(void) {
  int n, i = 0; // i will be our index variable.

  printf("Enter an int: ");
  scanf("%i", &n);

  while (i < n) {
    printf("%i\n", i);
    i = i + 1;
  }

  return 0;
}

/****
 *
 * Note:
 *
 *   When the user enters a number N, this program prints the numbers from
 * 0 to N-1. This sequence was chosen deliberately, in preference to the more
 * everyday counting from 1 to N, to illustrate a common idea in C: Counting
 * starts at 0. This fact will be very important when we come to array access
 * later in the course, so it is good to get used to it now.
 *
 *   Of course you could easily rewrite this program to count from 1 to N
 * instead if you wanted, and it's a good exercise to do so. Just don't forget
 * the lesson: In C counting starts at 0.
 *
 * Exercises:
 *
 * 1) Using what you've learned about variables, assignments and conditions,
 *    can you make this loop print out a more interesting sequence?
 *    If you're unsure, start simple: try printing out the first 'n' even
 *    numbers. When you're feeling more confident try printing out the first
 *    'n' Fibonacci numbers.
 *
 * 2) Can you combine this loop with what you've leared about if statements
 *    to print out a sequence together with some property of each of the
 *    numbers in the sequence, for example even/odd-ness?
 *    E.g.:
 *       1 is ODD
 *       1 is ODD
 *       2 is EVEN
 *       3 is ODD
 *       5 is ODD
 *       8 is EVEN
 *       ...
 *
 * 3) Can you alter this program to print out only the nth Fibonacci number?
 *
 * 4) Can you construct loops to print the following sequence:
 *
 *                11, 12, 13, 21, 22, 23, 31, 32, 33
 *
 *    (Hint: You'll want to nest loops in the same manner that you nested 'if'
 *     tests in the previous exercise.)
 *
 * 5) (ADVANCED)
 *
 *    Mathematically inclined students may note that there is a "closed form"
 *    for the Fibonacci numbers:
 *
 *      F(n) = phi^n - ( -1 / phi)^n / sqrt(5).
 *
 *      where phi = 1.6180339887...    is the Golden Ratio
 *        and  ^  is the exponetial operator.
 *
 *    Try to rewrite the program to compute the nth Fibonacci number from this
 *    closed form, using a loop to compute the exponentials, and floating point
 *    variables to hold the constants phi and sqrt(5).
 *
 ****/
