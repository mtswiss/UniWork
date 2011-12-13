#include <stdio.h>

int main(void) {

  // Define a variable 'lightswitch' using an enumeration.
  // Possible values for 'lightswitch' are 'on' and 'off'.
  enum { on, off } lightswitch;

  lightswitch = on;

  // If test prints whether the lights is on or off.
  if (lightswitch == on) {
    printf("lightswitch is on.\n");
  } else {
    printf("lightswitch is off.\n");
  }

  lightswitch = off;

  // Exact same test as before. Output will be different,
  // since the value of lightswitch is now 'off'.
  if (lightswitch == on) {
    printf("lightswitch is on.\n");
  } else {
    printf("lightswitch is off.\n");
  }

  return 0;
}

/****
 *
 * Note:
 *
 *   Enumerations introduce named integer constants. In the example
 * above these constants are named 'on' and 'off'. The names within an
 * enumeration are guaranteed to have distinct integer values, however
 * names from different enumerations are not, and since they really
 * are just integer constants C does not detect enum abuse. For
 * example, the following code is legal in C:
 *
 *    int main(void) {
 *      enum { red, blue } colour;
 *      enum { sunny, rainy } weather;
 *      colour = sunny;
 *      weather = red;
 *      return 0;
 *    }
 *
 *  Note that this is ok even though color is assigned a value intended
 * for weather, and vice-versa.
 *
 *  As enums really are just integer constants C does not provide a nice
 * method for reading or printing them. In the upcoming typedefs
 * exercise we will see how we can use typedefs and string handling to
 * provide better I/O for enum values.
 *
 *  In short: Use enumerations to obtain named integer constants which are
 * guaranteed to be distinct. Just be careful to use enum values only with
 * variables of the appropriate type.
 *
 * Exercises:
 *
 * 1) Try adding an extra value (like 'dim') to the enumeration, and testing
 *    it with the if-tests. If lightswitch is set to dim you should print
 *    "lightswitch is dim".
 *
 * 2) Try adding a two enumerations for an air conditioner. One should be the
 *    aircon temperature, with values such as 'cold', 'cool' 'warm' and 'hot'.
 *    the other should be the fan speed, with values such as 'slow',
 *    'medium' and 'fast'.
 *
 ****/
