#include <math.h>
#include <stdio.h>

int main(void) {
  float A, B, H;
  float ah, bh;

  printf("Enter the length of the hypotenuse, H: ");
  scanf("%f", &H);

  printf("Enter the length of side A: ");
  scanf("%f", &A);

  B = sqrt(pow(H, 2) - pow(A, 2));

  printf("The length of side B is %f\n", B);

  ah = acos(A / H) * (180 / M_PI);
  bh = asin(A / H) * (180 / M_PI);

  printf("Angle AH is %f degrees, angle BH is %f degrees.\n", ah, bh);
  printf("AH + BH = %f.\n", ah + bh);

  return 0;
}
