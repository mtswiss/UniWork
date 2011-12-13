#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define ROWS 5
#define COLS 5

// Sadly we must pin down the dimension of 2d arrays in parameter lists,
// which we did not have to do with 1d arrays. We will discover how to
// overcome this limitation later.
void fill_2d_array(int m[ROWS][COLS], int rows, int cols, int val) {
  int i, j;

  for (i = 0; i < rows; ++i) {
    for (j = 0; j < cols; ++j) {
      m[i][j] = val;
    }
  }
}

void print_2d_array(int m[ROWS][COLS], int rows, int cols) {
  int i, j;

  for (i = 0; i < rows; ++i) {
    printf("[ ");
    for (j = 0; j < cols; ++j) {
      printf("%2i ", m[i][j]);
    }
    printf("]\n");
  }
}

void add_2d_array(int m[ROWS][COLS], int n[ROWS][COLS], int rows, int cols) {
  int i, j;

  for (i = 0; i < rows; ++i) {
    for (j = 0; j < cols; ++j) {
      m[i][j] = m[i][j] + n[i][j];
    }
  }
}

void sub_2d_array(int m[ROWS][COLS], int n[ROWS][COLS], int rows, int cols) {
  int i, j;

  for (i = 0; i < rows; ++i) {
    for (j = 0; j < cols; ++j) {
      m[i][j] = m[i][j] - n[i][j];
    }
  }
}

void smul_2d_array(int m[ROWS][COLS], int k, int rows, int cols) {
  int i, j;

  for (i = 0; i < rows; ++i) {
    for (j = 0; j < cols; ++j) {
      m[i][j] = k * m[i][j];
    }
  }
}


int main(void) {
  int m1[ROWS][COLS], m2[ROWS][COLS], i, j;

  fill_2d_array(m1, ROWS, COLS, 7);
  printf("m1:\n");
  print_2d_array(m1, ROWS, COLS);

  for (i = 0; i < ROWS; ++i) {
    for (j = 0; j < COLS; ++j) {
      m2[i][j] = i * j;
    }
  }
  printf("m2:\n");
  print_2d_array(m2, ROWS, COLS);

  add_2d_array(m1, m2, ROWS, COLS);
  printf("m1 (with m2 added):\n");
  print_2d_array(m1, ROWS, COLS);

  smul_2d_array(m2, 2, ROWS, COLS);
  printf("m2 (multiplied by 2):\n");
  print_2d_array(m2, ROWS, COLS);

  return 0;
}
