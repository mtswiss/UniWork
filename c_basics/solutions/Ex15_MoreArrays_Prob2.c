#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define ASIZE 5
#define BSIZE 10

void fill_array(int a[], int size, int val) {
  int i;
  for (i = 0; i < size; ++i) {
    a[i] = val;
  }
}

void fill_array_random(int a[], int size, int m) {
  int i;
  for (i = 0; i < size; ++i) {
    a[i] = rand() % m;
  }
}


void print_array(int a[], int size) {
  int i;
  printf("[ ");
  for (i = 0; i < size; ++i) {
    printf("%i ", a[i]);
  }
  printf("]"); // Note: No newline.
}

void copy_array(int dst[], int src[], int num) {
  int i;
  for (i = 0; i < num; ++i) {
    dst[i] = src[i];
  }
}

void reverse_array(int a[], int size) {
  int i = 0, j = size - 1;
  int t; // t will be our "temporary" variable.

  while (i < j) {
    // These three lines swap a[i] and a[j] using the temporary variable.
    t = a[i];
    a[i] = a[j];
    a[j] = t;

    // Step in one from the left, and one from the right.
    i = i + 1;
    j = j - 1;
  }
}

int main(void) {
  int a[ASIZE], b[BSIZE];

  printf("a = ");
  print_array(a, ASIZE);
  printf("  (uninitialized)\n");

  fill_array_random(a, ASIZE, 100);
  printf("a = ");
  print_array(a, ASIZE);
  printf("  (randomly filled)\n");

  reverse_array(a, ASIZE);
  printf("a = ");
  print_array(a, ASIZE);
  printf("  (reversed)\n");

  fill_array(b, BSIZE, 7);
  printf("b = ");
  print_array(b, BSIZE);
  printf(" (filled with 7s)\n");

  copy_array(b, a, ASIZE);
  printf("b = ");
  print_array(b, BSIZE);
  printf(" (a copied over front)\n");

  reverse_array(b, BSIZE);
  printf("b = ");
  print_array(b, BSIZE);
  printf("  (reversed)\n");

  return 0;
}
