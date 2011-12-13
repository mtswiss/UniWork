#include <stdio.h>
#include <string.h>

int my_strcmp(char* s1, char* s2) {
  // We will use pointer arithmetic to move the s1 and s2 pointers through
  // their respective strings, looking for a mismatch:

  while (*s1 == *s2) {
    if (*s1 == 0) {
      // If we arrive here *s1 == *s2 == 0, so we've reached the end of
      // matching strings. We'll return zero right away (terminating the loop
      // and the function).
      return 0;
    } else {
      // Matching non-null-terminator characters. Keep moving through the
      // strings:
      ++s1;
      ++s2;
    }
  }

  // If we get here we must have had a mismatch. if *s1 is greater than *s2, 
  // so return 1, otherwise *s1 must be less than *s2, so return -1.
  if (*s1 > *s2) {
    return 1;
  } else {
    return -1;
  }
}

int main(void) {
  int order;
  char word1[21], word2[21];

  printf("Enter word 1: ");
  scanf("%20s", word1);
  printf("Enter word 2: ");
  scanf("%20s", word2);

  order = my_strcmp(word1, word2);

  if (order < 0) {
    printf("%s comes before %s in the dictionary.\n", word1, word2);
  } else if (order > 0) {
    printf("%s comes after %s in the dictionary.\n", word1, word2);
  } else {
    printf("%s is exactly the same as %s.\n", word1, word2);
  }

  return 0;
}
