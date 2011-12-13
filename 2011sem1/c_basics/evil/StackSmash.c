#include <stdio.h>

int main(void) {
  char word[21];

  printf("Enter a word: ");
  scanf("%s", word);
  printf("You entered %s.\n", word);

  return 0;
}

/****
 *
 * This program looks innocent enough, right?
 *
 * Well it isn't. It contains a very serious security vulnerability.
 *
 * Anyone can crash this program simply by entering a string that's too long
 * to fit in the 20 characters allottedfor 'word'.
 *
 * Try entering "This_isn't_so_much_a_word_as_it_is_a_short_essay." (all one
 * word) and see what happens.
 *
 * What's worse: On many systems a skilled hacker could have this program
 * execute arbitrary code on their behalf. Code that will execute with
 * _your_ security permissions. (Leaving it free to install a keylogger on
 * your account, for instance, or to delete all your files).
 *
 * The problem is that we used the "%s" conversion specifier in scanf without
 * supplying a width. That means that scanf will write as many characters as
 * the user supplies into memory starting at the beginning of the array
 * 'word'. If the user supplies 20 characters or less we're fine, but if they
 * supply more scanf will just keep writing right off the end of the array and
 * out into the stack. Eventually it will overwrite the return address of the
 * function. As noted a skilled attacker can craft a string that will replace
 * the legitimate return address of the function with an address of their
 * chosing, allowing the execution of their code. Even a clumsy attacker can
 * clobber the return address with a "random" value, which will result in
 * undefined behaviour by your program (almost certainly a crash).
 *
 * How can we avoid this?
 *
 * _Always_ use a width specifier when you read a string with scanf. The
 * following is safe:
 *
 *  scanf("%20s", word);
 *
 *
 * Note that printf does not suffer this issue, since it only reads from the
 * array but does not write to it. The printf call in this exercise, which
 * uses "%s", is perfectly safe as it is, once we've fixed the scanf bug.
 *
 ****/
