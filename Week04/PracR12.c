#include <stdio.h>

/* Program that sums integers for 1 to num	
** where num is a user input.
** Only the odd numbers are printed out when
** the numbers are sumed. 
** NGUYEN Minh Tuan
*/


int main()
{
	/* Initializing the variables */
	int num=0, i=0, sum=0;
	
	if(scanf("%d", &num)!=1)
	{return(-1);}
	
	/* Exception */
	if(num<=0)
	{
		return -1;
	}	

	/* While loop that goes though each int between and num and sums them up */
	while(i<=num)
	{	
		sum = i + sum;

		/* Prints out odd number */
		if((sum%2)!=0)
		{
			printf("%d ", sum);
		}		
		i++; 
	}
	printf("\n");
	return 0;
}
