#include <stdio.h>

void foo(void) {
  printf("foo.\n");
}

void bar(void) {
  printf("bar.\n");
}

void baz(void) {
  printf("baz.\n");
}

int bad(int b) {
  printf("bad: %i.\n", b);
  return 0;
}

int main(void) {
  void (*f)(void);
  
  f = &foo;
  (*f)();

  f = &bar;
  (*f)();

  f = &baz;
  (*f)();

  f = &bad; // Compiler will complain: function pointer types don't match.
            //
            //             void (*)(void) vs int (*)(int)
            //
            // Assigning &bad to f would be like trying to point an int* at a
            // float. You can do it, but it's not a good idea at all.
  (*f)();

  return 0;
}
