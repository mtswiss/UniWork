#include<stdio.h>

int a =0;

void f()
{
	int a = 1;
	int b = 2;
	{
		int b = 3;
		int c = 4;
		{
			int c = 5;
		}
	}
	printf("%d %d %d", a, b, c);
}

int main()
{
	f();
	
	return 0;
}
	
