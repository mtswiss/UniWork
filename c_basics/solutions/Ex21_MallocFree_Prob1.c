#include <stdio.h>
#include <stdlib.h>

struct person {
  char name[21]; // Changed to fixed sized array to hold non-const name.
  int age;
};

void print_person(struct person p) {
  printf("%s is %i years old.\n", p.name, p.age);
}

void array_of_structs_example(void) {
  int num_people = 3;
  int i;

  struct person* people = malloc(num_people * sizeof(people[0]));

  for (i = 0; i < num_people; ++i) {
    scanf("%20s %i", people[i].name, &people[i].age);
  }

  printf("array:\n");
  for (i = 0; i < num_people; ++i) {
    printf("Element %i: ", i);
    print_person(people[i]);
  }

  free(people);
}

int main(void) {
  array_of_structs_example();
  return 0;
}
