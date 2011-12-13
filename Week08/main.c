
#include	"pracquiz.h"
	
int
main(void)
{
	char    *s;

	while ((s = Get_line()))
	{
		/* echo input for debugging
		printf("read : [%s]\n", s); 
		*/
		pracquiz(s);
		printf("\n");
	}
	return 0;
}

