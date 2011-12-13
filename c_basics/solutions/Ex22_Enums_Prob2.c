#include <stdio.h>

int main(void) {

  // Define a variable 'lightswitch' using an enumeration.
  // Possible values for 'lightswitch' are 'on' and 'off'.
  enum { on, off } lightswitch;
  enum { cold, cool, warm, hot } aircon_temp;
  enum { slow, medium, fast } aircon_fan; 

  lightswitch = on;
  aircon_temp = warm;
  aircon_fan = fast;

  return 0;
}
