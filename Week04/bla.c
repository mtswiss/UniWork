#include<stdio.h>

main()
{
	int a=0, b=1, x=0, z=0, i;
	scanf("%d",&i);
	while(z<i)
	{
		printf("%d\n",b);
		x=b;
		b=a+b;
		a=x;
		z++;
	}
}	
