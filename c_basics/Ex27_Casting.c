#include <stdio.h>

int main(void) {
  int a = 5, b = 3;
  float f;  

  f = a / b;
  printf("f is %f.\n", f);

  f = a / (float)b; // <- Cast 'b' to float type.
  printf("f is %f.\n", f);

  return 0;
}

/****
 *
 * Note:
 *
 *   Casting tells the compiler to treat the value as something other than what
 * it would normally be treated as. In this case we have two ints. Doing a
 * division of two ints causes C to use integer division (naturally), and so
 * we get an integer result. So 5 / 3 is 1 (remainder 2).
 *
 *   By adding the (float) cast we tell C to treat b as a floating point value
 * in this instance. Dividing an integer by a float gives you a floating point
 * division, and so the answer is 1.66666.....
 *
 * 1) What happens if you add the following line to the program:
 *
 *                    printf("f is %i.\n", (int)f);
 *
 *     ?
 *
 ****/
