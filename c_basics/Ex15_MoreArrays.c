#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define ASIZE 5
#define BSIZE 10

// Fill an array with a given value.
void fill_array(int a[], int size, int val) {
  int i;
  for (i = 0; i < size; ++i) {
    a[i] = val;
  }
}

// Fill an array with random values between 0 and m.
void fill_array_random(int a[], int size, int m) {
  int i;
  for (i = 0; i < size; ++i) {
    a[i] = rand() % m;
  }
}


// Print the contents of an array.
void print_array(int a[], int size) {
  int i;
  printf("[ ");
  for (i = 0; i < size; ++i) {
    printf("%i ", a[i]);
  }
  printf("]"); // Note: No newline.
}

// Copy 'num' elements from array 'src' into array 'dst'.
// Space for 'dst' must be allocated already.
void copy_array(int dst[], int src[], int num) {
  int i;
  for (i = 0; i < num; ++i) {
    dst[i] = src[i];
  }
}

int main(void) {
  int a[ASIZE], b[BSIZE];

  // Print uninitialised a
  printf("a = ");
  print_array(a, ASIZE);
  printf("  (uninitialized)\n");

  // Fill a with random values 0 - 99, print it again.
  fill_array_random(a, ASIZE, 100);
  printf("a = ");
  print_array(a, ASIZE);
  printf("  (randomly filled)\n");

  // Fill b with 7s, print it.
  fill_array(b, BSIZE, 7);
  printf("b = ");
  print_array(b, BSIZE);
  printf(" (filled with 7s)\n");

  // Copy a into b, print b.
  copy_array(b, a, ASIZE);
  printf("b = ");
  print_array(b, BSIZE);
  printf(" (a copied over front)\n");

  return 0;
}

/****
 *
 * Exercises:
 *
 * 1) Write a function to add a number 'n' to every element of an array.
 *
 * 2) Write a function to reverse an array.
 *
 */

