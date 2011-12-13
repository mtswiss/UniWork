#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
  int secret, guess, finished = 0;

  // Uncomment the following line to seed the random number
  // generator with the system time. This will cause the
  // game to pick a different random number each time you
  // play.

  // srand(time(NULL));

  secret = rand() % 100;

  while (finished == 0) {
    printf("Enter your guess (0 to 99): ");

    if (scanf("%i", &guess) != 1) {
      printf("Invalid numeric input. Terminating.\n");
      exit(1);
    }

    if (guess < 0 || guess > 99) {
      printf("Guess is out of range. Please try again.\n");
    } else if (guess > secret) {
      printf("Too high, try again.\n");
    } else if (guess < secret) {
      printf("Too low, try again.\n");
    } else {
      printf("You guessed right!\n");
      finished = 1;
    }
  }
  return 0;
}
