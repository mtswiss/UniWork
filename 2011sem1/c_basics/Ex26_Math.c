#include <math.h> // <- New header. Gives us access to standard C math library.
#include <stdio.h>

int main(void) {

  double d = 13.5;

  printf("d = %f\n", d);
  printf("ceiling of d = %f\n", ceil(d));
  printf("floor of d = %f\n", floor(d));
  printf("sin(d) = %f\n", sin(d));
  printf("cos(d) = %f\n", cos(d));
  printf("log_2(d) = %f     (note: log_2 = log base 2)\n", log2(d));
  printf("d^2 = %f\n", pow(d, 2));
  printf("d^3 = %f\n", pow(d, 3));

  return 0;
}

/****
 *
 * Exercises:
 *
 * 1) Run 'man math.h' from the command line and scroll down to see the huge
 *    number of mathematical functions to which you have access via math.h.
 *
 * 2) Try using the power (pow), square root (sqrt), and trig functions (sin,
 *    cos, tan) to do some high-school trigonometry on right angled trianges.
 *    E.g. ask the user for the lengh of the hypotenuse and on side of a
 *    right angled triange. Store these values as doubles. Use that
 *    information to calculate the length of the 3rd side of the triangle and
 *    each of the three angles.
 *
 ****/
