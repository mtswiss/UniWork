#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define ROWS 5
#define COLS 5

int main(void) {
  int matrix[ROWS][COLS], i, j;

  // Initialise matrix.
  for (i = 0; i < ROWS; ++i) {
    for (j = 0; j < COLS; ++j) {
      matrix[i][j] = i * j;
    }
  }

  // Print matrix.
  for (i = 0; i < ROWS; ++i) {
    printf("[ ");
    for (j = 0; j < COLS; ++j) {
      printf("%2i ", matrix[i][j]);
    }
    printf("]\n");
  }

  return 0;
}

/****
 *
 * Exercises:
 *
 * 1) If you're unsure how the loops operate then hypothesize,
 *    and insert debugging output statements (printf calls) to
 *    test your theories.
 *
 * 2) Experiment with a more complex initialization
 *    expression, ideally one not symmetric in i and j.
 *
 * 3) Write fill_2d_array, print_2d_array, etc. functions
 *    comparable to those from the previous exercise.
 *    (leave out reverse as it doesn't make sense in 2d).
 *
 * 4) Write matrix addition, subtraction and scalar
 *    multiplication functions.
 *
 */
