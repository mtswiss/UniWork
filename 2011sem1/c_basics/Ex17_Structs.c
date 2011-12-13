#include <stdio.h>
#include <stdlib.h>

struct rational {
  int numer, denom;
};

// Print out a rational number as "a/b".
void print_rat(struct rational r) {
  printf("%i/%i", r.numer, r.denom);
}

// Read in a rational number from the keyboard.
struct rational scan_rat(void) {
  struct rational r;

  if (scanf("%i %i", &r.numer, &r.denom) != 2) {
    printf("Invalid rational number!\n");
    exit(1);
  }

  return r;
}

// Return 1 if the given fraction is improper, 0 otherwise.
int is_improper(struct rational r) {
  int improper = 0;

  // The 'abs' function return the absolute value of an integer. It is declared
  // in stdlib.h

  if (abs(r.numer) >= abs(r.denom)) {
    improper = 1;
  }

  return improper;
}

int main(void) {
  struct rational r;

  printf("Rational numbers should be entered as a numerator and denominator,\n");
  printf("separated by a space.\n");
  printf("\n");
  printf("Enter a rational number: ");

  r = scan_rat();
  printf("You entered ");
  print_rat(r);

  if (is_improper(r)) {
    printf(", which is improper.\n");
  } else {
    printf(", which is proper.\n");
  }

  return 0;
}

/****
 *
 * Exercises:
 *
 * 1) Write a functions to multiply a rational by a scalar. It should take an
 *    int and a rational as parameters, and return a rational as a result.
 *
 *    Remember: k * (a / b) = (ka / b)
 *
 *    Alter your main function to do the following:
 *      - Read a rational    (you can leave the existing code in place for this)
 *      - Read an int
 *      - Multiply them, using your new function.
 *      - Print out the result, using printRat.
 *
 * 2) Write a function to invert a rational. The rule is: (a / b)^-1 = (b / a)
 *
 * 3) Write a function to multiply pairs of rationals. The rule is:
 *
 *                  a     c     ac
 *                  -  *  -  =  --
 *                  b     d     bd
 *
 * 4) Write a function to add pairs of rationals. The rule is:
 *
 *                  a     c     da + bc
 *                  -  +  -  =  -------
 *                  b     d       bd
 *
 * 5) (ADVANCED)
 *
 *    Our current implementation allows for multiple representations of the
 *    same rational value. For instance one half can be represented as
 *    (1/2), (2/4), (3/6), (4/8), ....
 *
 *    This makes equality comparison for rationals problematic. What we want
 *    is to reduce the all rationals to their lowest terms. Comparison can
 *    then be made between these irreducible forms.
 *
 *    To lower the fractions we need to divide the numerator and denominator by
 *    their greatest common divisor, which can be found using Euclid's
 *    algorithm:
 *
 *      int gcd(int a, int b) {
 *        int t;
 *        while (b != 0) {
 *          t = b;
 *          b = a % b;
 *          a = t;
 *        }
 *        return a;
 *      }
 *
 *    Write a function 'simplify' that takes a rational as a parameter and
 *    returns the irreducible form of that fraction as its result. Modify your
 *    rational arithmetic functions to simplify their results before returning
 *    them.
 *
 *    Write the now trivial rational equality test.
 *
 * 6) (ADVANCED)
 *
 *    Write a similar program for three dimensional vectors, using the
 *    following struct as a basis.
 *
 *    struct Vector {
 *      float x, y, z;
 *    };
 *
 *    Write print and read functions, arithmetic, equality, as well as length,
 *    dot product and cross product functions.
 *
 *    Note: This could have been done with a 3-element array instead, which
 *    would carry the advantage that many Vector functions would work equally
 *    well for N-dimensional vectors. We use a struct here just as an exercise.
 *
 ****/
