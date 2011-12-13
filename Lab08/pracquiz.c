#include<stdio.h>
#include<ctype.h>

void pracquiz(char *str)
{
	int count=0;
	while(*str!= '\0' )
	{
		char * vowels= "aeiou";
		while(*vowels!= '\0')
		{
			if(tolower(*str)==*vowels)
				count++;
			vowels++;
		}
		str++;
	}
	printf("%i", count);
	if(count %2!=0)
		printf("*");
}
