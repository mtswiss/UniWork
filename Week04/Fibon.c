#include<stdio.h>

/* 
**	Fibonacci calculation program:
**	input - positive integer between 1-46 stored as i
**		  (46 because above that it goes over the limit)
**	output - Fibonacci numbers until the i-th number
*/

int main(void)
{
	int i;
	scanf("%d",&i);
	if(i>0 && i<47)
	{
		int a=0, b=1, c=0, z=0;
		while(z<i)
		{
			printf("%d ",b);
			c=b;
			b=a+b;
			a=c;
			z++;
		}
		printf("\n");
		return 0;
	}
	else
		return -1;
}	
