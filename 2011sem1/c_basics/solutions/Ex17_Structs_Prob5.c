#include <stdio.h>
#include <stdlib.h>

struct rational {
  int numer, denom;
};

// Euclid's Algorithm for finding the greatest common divisor of a pair
// of numbers a and b. See http://en.wikipedia.org/wiki/Euclidean_algorithm .
int gcd(int a, int b) {
  int t;

  while (b != 0) {
    t = b;
    b = a % b;
    a = t;
  }

  return a;
}

// Transform a given rational into irreducible form.
struct rational simplify_rat(struct rational r) {
  int c = gcd(r.numer, r.denom);
  struct rational result;

  result.numer = r.numer / c;
  result.denom = r.denom / c;

  return result;
}

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

  return simplify_rat(r);
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

// Scalar multiplication of a rational number:
struct rational scalar_mul_rat(int k, struct rational r) {
  struct rational result;

  result.numer = k * r.numer;
  result.denom = r.denom;

  return simplify_rat(result);
}

// Invert a rational number:
struct rational invert_rat(struct rational r) {
  struct rational result;

  result.numer = r.denom;
  result.denom = r.numer;

  return simplify_rat(result);
}

// Multiply a pair of rationals:
struct rational rat_mul_rat(struct rational r1, struct rational r2) {
  struct rational result;

  result.numer = r1.numer * r2.numer;
  result.denom = r1.denom * r2.denom;

  return simplify_rat(result);
}

// Add a pair of rationals:
struct rational rat_add_rat(struct rational r1, struct rational r2) {
  struct rational result;

  result.numer = (r1.numer * r2.denom) + (r2.numer * r1.denom);
  result.denom = r1.denom * r2.denom;

  return simplify_rat(result);
}

int main(void) {
  struct rational r1, r2, r3, r4, r5;
  int k;

  printf("Rational numbers should be entered as a numerator and denominator,\n");
  printf("separated by a space.\n");
  printf("\n");
  printf("Enter a rational number: ");
  r1 = scan_rat();

  printf("Enter an integer: ");
  scanf("%i", &k);

  r2 = scalar_mul_rat(k, r1);

  printf("%i * ", k);
  print_rat(r1);
  printf(" = ");
  print_rat(r2);
  printf("\n");

  r3 = invert_rat(r2);

  printf("The inverse of ");
  print_rat(r2);
  printf(" is ");
  print_rat(r3);
  printf("\n");

  r4 = rat_mul_rat(r2, r3);

  print_rat(r2);
  printf(" * ");
  print_rat(r3);
  printf(" = ");
  print_rat(r4);
  printf("   ... (Curious. Why always (A/A)? Check the code!).\n");

  r5 = rat_add_rat(r2, r3);

  print_rat(r2);
  printf(" + ");
  print_rat(r3);
  printf(" = ");
  print_rat(r5);
  printf("\n");

  return 0;
}
