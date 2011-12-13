#includes<stdio.h>

int main()
{
	int num, x, i, sum;
	num=0, x=1, sum=0;
	scanf("%d", &x);
	if(x<0)
		return -1;
		
	while(i<=x)
	{	
		sum = i + sum;
		if((sum%2)!=0)
			printf("%d ", sum);
		i++; 
	}
	return 0;
}
