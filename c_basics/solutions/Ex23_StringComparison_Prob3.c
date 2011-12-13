#include <stdio.h>
#include <string.h>

int main(void) {
  int order;
  char word1[21], word2[21];

  printf("Enter word 1: ");
  scanf("%20s", word1);
  printf("Enter word 2: ");
  scanf("%20s", word2);

  order = strcmp(word1, word2);

  if (order < 0) {
    printf("%s comes before %s in the dictionary.\n", word1, word2);
  } else if (order > 0) {
    printf("%s comes after %s in the dictionary.\n", word1, word2);
  } else {
    printf("%s is exactly the same as %s.\n", word1, word2);
  }

  // Note: The 'z' modifier is for printing 'size_t' values.
  // size_t is an integer type intended for representing sizes of things in
  // memory, such as strings.
  printf("The length of \"%s\" is %zu.\n", word1, strlen(word1));
  printf("The length of \"%s\" is %zu.\n", word2, strlen(word2));

  return 0;
}
