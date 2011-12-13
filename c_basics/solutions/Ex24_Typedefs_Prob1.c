#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { cold, cool, warm, hot } aircon_temp;
typedef enum { slow, medium, fast } aircon_fanspeed;

typedef struct {
  char name[21];
  aircon_temp t;
  aircon_fanspeed f;
} room;

char* aircon_temp_to_string(aircon_temp t) {
  char* aircon_temp_str;

  if (t == cold) {
    aircon_temp_str = "cold";
  } else if (t == cool) {
    aircon_temp_str = "cool";
  } else if (t == warm) {
    aircon_temp_str = "warm";
  } else if (t == hot) {
    aircon_temp_str = "hot";
  } else {
    aircon_temp_str = "bad aircon temperature";
  }

  return aircon_temp_str;
}

aircon_temp string_to_aircon_temp(char* s) {
  aircon_temp state;

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

char* aircon_fanspeed_to_string(aircon_fanspeed f) {
  char* aircon_fanspeed_str;

  if (f == slow) {
    aircon_fanspeed_str = "slow";
  } else if (f == medium) {
    aircon_fanspeed_str = "medium";
  } else if (f == fast) {
    aircon_fanspeed_str = "fast";
  } else {
    aircon_fanspeed_str = "bad aircon fanspeed";
  }

  return aircon_fanspeed_str;
}

aircon_fanspeed string_to_aircon_fanspeed(char* s) {
  aircon_fanspeed state;

  if (strcmp(s, "slow") == 0) {
    state = slow;
  } else if (strcmp(s, "medium") == 0) {
    state = medium;
  } else if (strcmp(s, "fast") == 0) {
    state = fast;
  } else {
    printf("You have entered an invalid aircon fan speed. Program terminating.\n");
    exit(1);
  }

  return state;
}

void print_room(room r) {
  printf("In the %s, the aircon setting is %s/%s.\n",
         r.name, aircon_temp_to_string(r.t), aircon_fanspeed_to_string(r.f));
}

void scan_room(room *r) {
  char aircon_temp_str[5], // Big enough for "cold" + a null terminator.
       aircon_fan_str[7];  // Big enough for "medium" + a null terminator.

  scanf("%20s %4s %6s", r->name, aircon_temp_str, aircon_fan_str);

  r->t = string_to_aircon_temp(aircon_temp_str);
  r->f = string_to_aircon_fanspeed(aircon_fan_str);
}

int main(void) {
  room r;

  // Here we use a nifty trick: You can break long strings over multiple lines
  // by just terminating the string one one line (with a closing quote), then
  // immediately opening it on the next line.

  printf("Enter a room (<room name> (\"cold\"|\"cool\"|"
         "\"warm\"|\"hot\") (\"slow\"|\"medium\"|\"fast\")): ");

  scan_room(&r);
  print_room(r);

  return 0;
}
