#include <stdio.h>

int main(void) {

  signed int sn = -10; // Legal, but redundant: ints are signed by default.
  unsigned int un = 5; // An unsigned int holds non-negative values.

  printf("sn is %i, un is %u\n", sn, un); // Note: %u for the unsigned.

  return 0;
}

/****
 *
 * Note:
 *
 *  The 'signed' and 'unsigned' qualifiers apply to both of the 'integral'
 * types (char and int), but not to the floating point types (float and
 * double). Floats and doubles are always signed, and the compiler will
 * report an error if you try to attach the signed or unsigned qualifiers to
 * either of these types.
 *
 * Exercises:
 *
 * 1) What happens if you try to store a negative value in an unsigned int?
 *
 * 2) What happens if you subtract one from an unsigned int which currently
 *    holds the value zero?
 *
 */
