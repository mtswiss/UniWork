#include<stdio.h>
#include<limits.h>

/* 
**	Program that prints out the multiples of num2 
**	until it reaches num1
*/

int main(void)
{
	int num1, num2, i, x, num3;
	num1=0;
	num2=0;
	scanf("%d %d", &num1, &num2);
	
	if(num1<=INT_MAX && num2<=INT_MAX && num1/num2>0 && num1>0 && num2>0)
	{
		/*	create an int that represents the number of 
		**	times num1 is divisible by num2 and call it x
		*/
		x = num1/num2;
	
		/*	loop thourgh each number from 1 to x
		**	and multiply it by num2
		*/
		for(i=1;i<=x;i++)
		{
			num3 = i*num2;
			if(num3!=num1)
			printf("%d ",num3);
		}
		printf("\n");
		return 0;
	}
	else
	{
		return -1;
	}


	return 0;
}
