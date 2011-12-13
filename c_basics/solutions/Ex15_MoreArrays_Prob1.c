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

void add_n_to_array(int a[], int size, int n) {
  int i;
  for (i = 0; i < size; ++i) {
    a[i] = a[i] + n;
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

  add_n_to_array(a, ASIZE, 5);
  printf("a = ");
  print_array(a, ASIZE);
  printf("  (added 5 to every element)\n");

  fill_array(b, BSIZE, 7);
  printf("b = ");
  print_array(b, BSIZE);
  printf(" (filled with 7s)\n");

  copy_array(b, a, ASIZE);
  printf("b = ");
  print_array(b, BSIZE);
  printf(" (a copied over front)\n");

  add_n_to_array(b, BSIZE, 3);
  printf("b = ");
  print_array(b, BSIZE);
  printf("  (added 3 to every element)\n");

  return 0;
}
