#include <stdio.h>
#include <string.h> // <- New header. Gives us access to C string handling
                    // functions like strcmp.

int main(void) {
  int order;
  char word1[21], word2[21];

  printf("Enter word 1: ");
  scanf("%20s", word1); // Note: No ampersand on argument 'word1' here.
                        // Reason: Arrays are implicitly convertible to
                        // pointers, no need to use the address-of
                        // operator.

  printf("Enter word 2: ");
  scanf("%20s", word2);

  // strcmp compares two strings, s1 and s2.
  // It returns 0 if s1 is equal to s2, < 0 if s1 comes before s2 in standard
  // dictionary (lexicographic) order, and > 0 if s1 comes after s2.

  order = strcmp(word1, word2);
  if (order < 0) {
    printf("%s comes before %s in the dictionary.\n", word1, word2);
  } else if (order > 0) {
    printf("%s comes after %s in the dictionary.\n", word1, word2);
  } else {
    printf("%s is exactly the same as %s.\n", word1, word2);
  }

  return 0;
}

/****
 * Exercises:
 *
 * 1) On the command line run 'man string.h'. Look at some of the functions
 *    which the C library provides for you. You can quit 'man' by pressing the
 *    'q' key.
 * 
 * 2) Using 'man' again take a closer look at functions like 'memcpy', 'strlen'
 *    and 'strdup'. You will find these functions useful in your day-to-day C
 *    coding.
 *
 * 3) Using the strlen function have your program output the length of words
 *    one and two at the end of the program above.
 *
 * 4) (ADVANCED)
 *
 *    Try implementing your own version of strcmp (call it 'my_strcmp'). It
 *    will have two parameters: the strings to be compared. It will have to
 *    loop checking that the characters at each index match, and will need
 *    to return +1 or -1 as soon as there is a mismatch.
 *
 *    Make sure that your function does not past the null terminator of either
 *    string.
 *
 ****/
