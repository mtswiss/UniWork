#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define ROWS 5
#define COLS 5

int main(void) {
  int matrix[ROWS][COLS], i, j;

  for (i = 0; i < ROWS; ++i) {
    for (j = 0; j < COLS; ++j) {
      matrix[i][j] = (2 * i) - j;
    }
  }

  for (i = 0; i < ROWS; ++i) {
    printf("[ ");
    for (j = 0; j < COLS; ++j) {
      printf("%2i ", matrix[i][j]);
    }
    printf("]\n");
  }

  return 0;
}
