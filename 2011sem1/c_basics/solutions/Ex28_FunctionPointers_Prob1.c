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

int main(void) {
  void (*f)(void);
  
  f = &foo;
  (*f)();

  f = &bar;
  (*f)();

  f = &baz;
  (*f)();

  return 0;
}
