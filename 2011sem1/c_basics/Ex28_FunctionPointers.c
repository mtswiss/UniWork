#include <stdio.h>

void foo(void) {
  printf("foo.\n");
}

void bar(void) {
  printf("bar.\n");
}

int main(void) {
  void (*f)(void); // <- f is a "function pointer". It points to a function
                   // which we call call via the dereferenced pointer.
  
  f = &foo; // Point f at foo.
  (*f)(); // Call the foo function via f.

  f = &bar; // Point f at bar.
  (*f)(); // Call the bar function via f.

  return 0;
}

/****
 *
 * Exercises:
 *
 * 1) Try adding a 3rd function with the same signature (i.e. returns void, has
 *    void parameter list). Add two statments to the end of main to point f
 *    at your function, then call it.
 *
 * 2) What happens if you declare yet another function, but with a different
 *    signature (for example returns an int, takes an int) and try to point
 *    f at it? Try this.
 *
 * 3) Create another function pointer 'g' with a declaration that matches the
 *    function you introduced in part 2. Point 'g' at your function an call it.
 *
 ****/
