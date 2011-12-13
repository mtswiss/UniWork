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

int notsobad(int b) {
  printf("no so bad: %i.\n", b);
  return 0;
}

int main(void) {
  void (*f)(void);
  int (*g)(int);  

  f = &foo;
  (*f)();

  f = &bar;
  (*f)();

  f = &baz;
  (*f)();

  g = &notsobad;
  (*g)(10);

  return 0;
}
