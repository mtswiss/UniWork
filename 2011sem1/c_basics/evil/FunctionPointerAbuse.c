#include <stdio.h>
#include <stdlib.h>


void pure_evil(int n) {
  printf("%i...\n", n);
  // ^^^ This is just a print statement. Nothing evil about that...

  (pure_evil + (exit - pure_evil) * (n / 10))(n + 1); /* EVIL */
  // ^^^ But what the hell is this thing? See below for the answer.
}

int main() {

  pure_evil(0);

  return 0;
}

/****
 *
 * The giveaway is the appearance of 'pure_evil' and 'exit' in the expression.
 * Both are function names. That hideous expression is a function pointer, and
 * whatever it points to is being called with (n - 1) as a parameter.
 * Confused? Read on...
 *
 * Look closely at the expression and you will see that (n / 10) is an integer
 * ivision. For 0 <= n < 10 the quotient of this division will be 0, and so
 * the expression simplifies as follows:
 *
 *    (pure_evil + (exit - pure_evil) * (n / 10))(n + 1)
 *  = (pure_evil + (exit - pure_evil) * 0)(n + 1)
 *  = (pure_evil + 0)(n + 1)
 *  = (pure_evil)(n + 1)
 *
 * So this is just a recursive call to 'pure_evil'. We've encountered
 * recursive calls before, albeit not via function pointers. Nothing too new
 * yet...
 *
 * But each recursive call increments the parameter n by one (starting from
 * the 0 which we pass in from main). So on the 11th recursive call n will be
 * exactly 10. What happens then? Well...
 *
 *    (pure_evil + (exit - pure_evil) * (n / 10))(n + 1)
 *  = (pure_evil + (exit - pure_evil) * (10 / 10))(n + 1)
 *  = (pure_evil + (exit - pure_evil) * (1))(n + 1)
 *  = (pure_evil + (exit - pure_evil) * 1)(n + 1)
 *  = (pure_evil + (exit - pure_evil))(n + 1)
 *  = (pure_evil + exit - pure_evil)(n + 1)
 *  = (pure_evil - pure_evil + exit)(n + 1)
 *  = (exit)(n + 1)
 *
 * So when n == 10, instead of simplifying to a recursive call to 'pure_evil',
 * our expression simplifies to a call to exit. The exit function will be
 * called with (n + 1), which is 11, and so our program will terminate right
 * here, nested 10 calls deep into 'pure_evil', without ever returning to
 * main.
 *
 * There's a reason this function is called 'pure_evil'. Apart from being
 * terribly confusing, it's also not standards compliant. According to the C99
 * standard arithmetic operations (which are ok for regular pointers) are
 * undefined for function pointers. Here we are relying on GNU extensions to
 * the standard, and there is _no_ guarantee that this code will compile, let
 * alone run, on any other compiler and/or platform. This is why the compiler
 * emits warnings for this statement (if warnings are turned on).
 *
 * In short: If you ever do this you're a bad person. Don't do it.
 *
 ****/
