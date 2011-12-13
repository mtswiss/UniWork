#include <stdio.h>

int main(void) {
  printf("\n"); // <- Move straight to a new line.
  printf("                     In sequential C,\n"); // <- Newline character.
  printf("               the flow of control proceeds,\n");
  printf("                    from top to bottom.\n");
  printf("\n");
  printf("                          @->--\n");
  printf("\n");
  printf("Note that lines of code "); // <- No newline character.
  printf("need not correspond ");
  printf("to lines of output.");
  printf("\n");
  return 0;
}
