#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { slow, normal, fast } fan_speed;
typedef enum { cold, cool, warm, hot } temperature;

char* temperature_to_string(temperature t) {
  char* temperature_str;

  switch (t) {
  case cold:
    temperature_str = "cold";
    break;
  case cool:
    temperature_str = "cool";
    break;
  case warm:
    temperature_str = "warm";
    break;
  case hot:
    temperature_str = "hot";
    break;
  default:
    temperature_str = "bad aircon temperature";
    exit(1);
    break;
  }

  return temperature_str;
}

temperature string_to_temperature(char* s) {
  temperature state;

  if (strcmp(s, "cold") == 0) {
    state = cold;
  } else if (strcmp(s, "cool") == 0) {
    state = cool;
  } else if (strcmp(s, "warm") == 0) {
    state = warm;
  } else if (strcmp(s, "hot") == 0) {
    state = hot;
  } else {
    printf("You have entered an invalid aircon temperature. Program terminating.\n");
    exit(1);
  }

  return state;
}

char* fan_speed_to_string(fan_speed s) {
  char* fan_speed_str;

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
  char fs_str[7], t_str[5];
  fan_speed s;  
  temperature t;

  printf("Enter a fan speed (\"slow\", \"normal\" or \"fast\"): ");
  scanf("%6s", fs_str);

  printf("Enter a temperature (\"cold\", \"cool\", \"warm\", \"hot\"): ");
  scanf("%4s", t_str);

  s = string_to_fan_speed(fs_str);
  t = string_to_temperature(t_str);

  printf("Fan speed: %s.\n", fan_speed_to_string(s));
  printf("Temperature: %s.\n", temperature_to_string(t));

  return 0;
}
