#include <stdio.h>

int main(void) {
  enum { on, dim, off } lightswitch;

  lightswitch = on;

  if (lightswitch == on) {
    printf("lightswitch is on.\n");
  } else if (lightswitch == dim) {
    printf("lightswitch is dim.\n");
  } else {
    printf("lightswitch is off.\n");
  }

  lightswitch = off;

  if (lightswitch == on) {
    printf("lightswitch is on.\n");
  } else if (lightswitch == dim) {
    printf("lightswitch is dim.\n");
  } else {
    printf("lightswitch is off.\n");
  }

  lightswitch = dim;

  if (lightswitch == on) {
    printf("lightswitch is on.\n");
  } else if (lightswitch == dim) {
    printf("lightswitch is dim.\n");
  } else {
    printf("lightswitch is off.\n");
  }

  return 0;
}
