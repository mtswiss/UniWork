#include <stdio.h>
#include <stdlib.h>

struct person {
  char* name;
  int age;
};

// Convenience function to print a person:
void print_person(struct person p) {
  printf("%s is %i years old.\n", p.name, p.age);
}

// Allocate and de-allocate a single int.
// This is just a basic example of malloc/free use. In practice you'd
// just use a plain int for such a basic purpose.
void int_example(void) {
  int *p;

  p = malloc(sizeof(*p)); // Allocate memory for a single byte.
  *p = 7;
  printf("%i\n", *p);
  free(p); // Free the byte.
}

// Allocate and de-allocate a single struct.
void struct_example(void) {
  struct person* p;

  p = malloc(sizeof(*p));
  p->name = "Alice";
  p->age = 21;
  print_person(*p);

  free(p);
}

// Allocate and deallocate an array of ints.
void array_example(void) {
  int num_ints = 10;
  int i;

  // Allocate space for the array.
  int* a = malloc(num_ints * sizeof(a[0]));

  // Initialise the array.
  for (i = 0; i < num_ints; ++i) {
    a[i] = rand() % 100;
  }

  // Print the array.
  printf("array = [ ");
  for (i = 0; i < num_ints; ++i) {
    printf("%i ", a[i]); // <- Note array access syntax.
  }
  printf("]\n");

  free(a); // <- Free the array.
}

int main(void) {
  int_example();
  struct_example();
  array_example();
  return 0;
}

/****
 *
 * Exercises:
 *
 * 1) Drawing on what you've learned from the examples above, write a function
 *    which allocates, populates, prints and then frees an array of People.
 *
 */
