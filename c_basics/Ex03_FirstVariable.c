#include <stdio.h>

int main(void) {
  int n = 42;                           // Declare and initialise n.
  printf("The value of n is %i.\n", n); // Print n (inside format string).
  return 0;
}

/****
 *
 * Note:
 *
 *   Variable names in C consist of a letter [a-zA-Z], followed by any
 * number of letters, underscores or numbers. The case of the letters is
 * significant: 'A' is a different variable from 'a'.
 *
 *   The following are all legal, distinct C variable names:
 *
 *   n
 *   N
 *   Index
 *   a_long_variable_name
 *   I_7
 *   Steve           <-- Do NOT call your variables Steve. This is only
 *   steve           <-- to illustrate that variables are case sensitive.
 *
 *   In C variables must always be declared before they are used. For
 * instance this is valid C code:
 *
 *   int n;
 *   n = 7;
 *
 *   However the following examples are not, because the variables are
 * used before they are defined:
 *
 *   x = 10;
 *
 *   OR
 *
 *   if (y == 3) ...
 *   int y = 3;
 *
 *   Make sure you always define your variables before you use them.
 *
 * Exercises:
 *
 * 1) What happens if you change the initialisation value for 'n' ?
 *
 * 2) Can you figure out how to print 'n' twice on a single line?
 *
 * 3) Can you make the program print "n - n = 0", with the appropriate
 *    value filled in?
 *
 * 4) Rename 'n' to something else, updating all uses in your program
 *    accordingly.
 *
 *
 *
 * An important note:
 *
 *                       On Meaningful Variable Names
 *
 *   Ideally you want your variable names to be meaningful, to tell you
 * something about what the variable represents. This is why "Steve" is such a
 * terrible variable name. What is a person to make of the expression
 *
 *                          Steve = Steve * 7    ?
 *
 *   However, while you want your variable names to be meaningful, you don't
 * want them to be so long that they impair readability. Compare the clarity of
 *
 *                              int age = 17;
 *
 *                                  with
 *
 *                     int this_is_a_persons_age = 17;
 *
 *   The art of good variable naming consists of picking names that impart
 * meaning without being so long that they impair readability. Over time you
 * will discover many helpful conventions for variable names (you will meet 'i'
 * for loop indexes soon). Where there is no convention to guide you, pick
 * something short but clear, and if there might be doubt as to its meaning
 * then clarify it with a comment where the variable is declared.
 *
 *
 *
 * One Final Note:
 *
 *                               For Pedants
 *
 *   You may discover that variables can also begin with an underscore, rather
 * than a letter. Do NOT name your variables this way. While the compiler will
 * allow it, it is extremely bad practice. Variable names starting with '_' or
 * '__' are reserved for use by compiler and standard library implementers.
 *
 ****/
