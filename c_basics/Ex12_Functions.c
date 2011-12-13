#include <stdio.h>

// factorial is a new C function.
// It takes one integer parameter (n), and returns an integer result.
int factorial(int n) {
  int i, result = 1;

  for (i = 1; i <= n; ++i) {
    result = result * i;
  }

  return result;
}

int main(void) {
  int n, r;

  printf("Enter an int: ");
  scanf("%i", &n);

  r = factorial(n);

  printf("n! is %i\n", r);

  return 0;
}

/****
 *
 * Note:
 *
 *   In Exercise 9 you were asked to write a loop which computed the factorial
 * of a number n. It would be very tedious to have to write this whole loop out
 * wherever you needed a factorial. The C language allows you to give a name to
 * a body of code so that you can execute the code simply by writing its name
 * (and passing any arguments it expects). The name can be anything that
 * follows the C identifier rules (the same ones that govern variable names).
 * Such a named body of code is called a "function", and they are one of the
 * most important and powerful abstractions in C.
 *
 *   You have actually written a function yourself (or at least edited one),
 * possibly without even realising you were doing it: the 'main' function.
 * Every C program needs a 'main' function, and the compiler understands it as
 * the special function that should be called by the system when your program
 * is executed.
 *
 *   In addition to writing your own function you have also made use of two
 * others: 'printf', the printing function, and 'scanf', the reading function.
 * These functions do not appear in your code, but their declarations were
 * "pulled in" to your program by the '#include <stdio.h>' line.
 *
 * Exercises:
 *
 * 1) Try writing a new function of one parameter (using 'factorial' as a
 *    guide). For instance write a 'square' function which squares its
 *    argument (or 'cube', or 'triangular', or whatever you like). Change
 *    main to call your new function rather than factorial, but leave the
 *    factorial function in your program.
 *
 * 2) Try extracting the "body" of the main function and placing it in a new
 *    function (call it "MyFunc", or whatever you like). Reduce the body of
 *    'main' to simply a call to your function, plus the return 0. I.e.
 *
 *       int main() {
 *         MyFunc();
 *         return 0;
 *       }
 *
 *
 * 3) What happens if you add an extra call to MyFunc to the body of 'main' so
 *    that there are two calls to "MyFunc" in sequence?
 *
 * 4) Your "MyFunc" function always returns the same value, namely 0. Given
 *    that fact, you may be asking whether you really have to return a value
 *    at all. The answer is "no". C provides a way to declare that a function
 *    does not return anything: the 'void' keyword (the same one you have been
 *    using in the parameter list of 'main'). Change the return type of your
 *    "MyFunc" function to 'void' (rather than int). What happens when you
 *    compile the program? (Hint - you will have to have to modify the body of
 *    MyFunc in response to a compiler error in order to get your program
 *    compiling again)
 *
 *
 * A final note:
 *
 *                    On the Return Value of 'main':
 *
 *    Why do we return "int" from main? And where does this value go?
 * The 'main' function is called by the operating system, and the return value
 * of main is returned to the operating system to indicate the success or
 * failure of the program. The convention is that a zero return value from main
 * indicates the successful termination of the program, and that a non-zero
 * return value from main indicates a failure of some sort. Often the exact
 * non-zero value will tell you something about what went wrong, i.e. non-zero
 * return values from main are usually a form of error code.
 *
 *   You can inspect the value returned by main when you run your program from
 * the command line, by echoing the value of the shell variable '$?' as
 * follows:
 *
 *        % gcc -o MyProg MyProg.c
 *        % ./MyProg
 *        % echo $?
 *
 *   This technique is frequently used by shell scripts rely on multiple
 * programs to make sure that each program terminates correctly before the next
 * is run.
 *
 *   It is a good exercise to write a minimal C program which returns a non-zero
 * return value from main and verify it using the technique described above.
 *
 ****/
