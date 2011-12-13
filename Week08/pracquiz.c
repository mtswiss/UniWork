#include<stdio.h> 
#include<ctype.h>

void pracquiz(char *str)
{
	while(*str!= '\0' )
	{
		if(ispunct(*str)==0)
			printf("%c",*str);
		str++;
	}
}
