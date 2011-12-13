#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Typedefs introduce short names for types. Here we use typedef to introduce
// an enumeration type called switch_state.
typedef enum { on, off } switch_state;

// Here we use typedef to define a structure type representing a room. Note
// the different placement of the type name. Usually we would write
//
//                       struct room { ... };
// 
// and we would always refer to the type as 'struct room'. However using a
// typedef we can write
//
//                   typedef struct { ... } room;
//
// and refer to the type as just 'room'. There is just one "gotcha" here. The
// name introduced by the typedef isn't available until after the struct has
// been defined, so we can't use it to define structs that refer to themselves,
// such as ListNode from the linked list exercise.
//
typedef struct {
  char name[21];
  switch_state s1, s2;
} room;

// Convert a switch state to a string.
char* switch_state_to_string(switch_state s) {
  char* switch_state_str;

  if (s == on) {
    switch_state_str = "on";
  } else if (s == off) {
    switch_state_str = "off";
  } else {
    switch_state_str = "bad switch state";
  }

  return switch_state_str;
}

// Convert a string to a switch state
switch_state string_to_switch_state(char* s) {
  switch_state state;

  if (strcmp(s, "on") == 0) {
    state = on;
  } else if (strcmp(s, "off") == 0) {
    state = off;
  } else {
    printf("You have entered an invalid switch state. Program terminating.\n");
    exit(1);
  }

  return state;
}

// Print out a room. Note the lack of 'struct' before the 'room' type. This is
// because we introduced 'room' using a typedef.
void print_room(room r) {
  printf("In the %s, switch 1 is %s and switch 2 is %s.\n",
         r.name, switch_state_to_string(r.s1), switch_state_to_string(r.s2));
}

// Read in a room. Note we take a pointer to the room variable so that we can
// modify it.
void scan_room(room *r) {
  char switch_str_1[4], switch_str_2[4];

  // Below we again omit the '&' on the parameters to scanf. strings are
  // arrays, and arrays are implicitly convertible to pointers, so the
  // '&' operator is unnecessary here.
  scanf("%20s %3s %3s", r->name, switch_str_1, switch_str_2);

  r->s1 = string_to_switch_state(switch_str_1);
  r->s2 = string_to_switch_state(switch_str_2);
}

int main(void) {
  room r;

  printf("Enter a room (<room name> (\"on\"|\"off\") (\"on\"|\"off\")): ");
  scan_room(&r);
  print_room(r);

  return 0;
}

/****
 *
 * Exercises:
 *
 * 1) Modify the program to track the state of an airconditioner in each room,
 *    rather than lightswitches. You'll need to introduce new enum typedefs for
 *    temperature and fan speed, functions to convert these enums to and from
 *    strings, and modify the room struct and print_room and scan_room
 *    functions accordingly.
 *
 ****/
