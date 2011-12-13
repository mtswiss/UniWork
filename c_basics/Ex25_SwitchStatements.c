#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { slow, normal, fast } fan_speed;

char* fan_speed_to_string(fan_speed s) {
  char* fan_speed_str;

  // Here we use a switch statement to handle each
  // possible value of s, rather than a series of
  // nested ifs.
  switch (s) {
  case slow:
    fan_speed_str = "slow";
    break;
  case normal:
    fan_speed_str = "normal";
    break;
  case fast:
    fan_speed_str = "fast";
    break;
  default:
    printf("Invalid fan_speed value. Terminating.\n");
    exit(1);
    break;
  }

  return fan_speed_str;
}

fan_speed string_to_fan_speed(char* fs_str) {
  fan_speed s;

  // We can't use a switch statement here: it needs to operate on a single
  // expression (like 's'), but we have multiple different expressions:
  // strcmp(fs_str, "slow") == 0, strcmp(fs_str, "normal") == 0, ...
  // So here we have to fall back on nested ifs.
  if (strcmp(fs_str, "slow") == 0) {
    s = slow; 
  } else if (strcmp(fs_str, "normal") == 0) {
    s = normal;
  } else if (strcmp(fs_str, "fast") == 0) {
    s = fast;
  } else {
    printf("Invalid fan_speed value. Terminating.\n");
    exit(1);
  }

  return s;
}

int main(void) {
  char fs_str[7];
  fan_speed s;  

  printf("Enter a fan speed (\"slow\", \"normal\" or \"fast\"): ");
  scanf("%6s", fs_str);

  s = string_to_fan_speed(fs_str);

  printf("Fan speed: %s.\n", fan_speed_to_string(s));

  return 0;
}

/****
 *
 * Exercises:
 *
 * 1) Add a temperature enumeration and provide functions to convert it to and
 *    from a string representation. Your "to string" version should use a
 *    switch statement. You may find your solution to the previous exercise
 *    useful, if you wrote it.
 *
 ****/
