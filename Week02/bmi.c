#include<stdio.h>

main()
{
	float weight;
	float height;
	/*printf("Please enter weight in kg. eg: 57.8\n"); */
	scanf("%f", &weight);
	/*printf("Please enter height in m. eg 1.78\n");*/
	scanf("%f", &height);
	printf("%f\n", weight/(height*height));
}
