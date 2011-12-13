#include<stdio.h>
#include<ctype.h>

void pracquiz(char *str)
{
	while(*str!= '\0' )
	{

printf("%i",ispunct(str));

/*		
		if(ispunct(str)==0)
		{
			printf("%s",str);
		}
*/		
		str++;
	}
}
