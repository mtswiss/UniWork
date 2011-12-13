#include<stdio.h>

main()
{
	int number;
	if(scanf("%d", &number)!=1);
	int set[number-1];
	int length = ( sizeof(set) / sizeof(int));
	int i=0;
	while(i<length)
	{	
		set[i]=i+2;
		i++;
	}		
	i=0;
	int j;
	while(i<length)
	{	
		if(set[i]!=0)	
		{
			j=i+1;	
			while(j<length)
			{	
				if(set[j]%set[i]==0)
				{
					if(set[j]!=0)
					{
						set[j]=0;
					}
				}
				j++;
			}		
		}
		i++;
	}
	i=0;
	int count=0;
	while(i<length)
	{
		if(set[i]!=0)
		{
			printf("%d\n", set[i]);
			count++;	
		}
		i++;
	}
}
