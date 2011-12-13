#include	<stdio.h>
#include	<ctype.h>
#include	<stdlib.h>
#include	<string.h>


/* Creating the format for the list item*/
typedef struct node 
{
	int x;
	struct node *next;
} Node;


/* Creating a new list */
Node *createlist(void)
{

	Node	*root;
	Node	*curr;

	Node	*new;
	
	int	*str, buffer;

	root = (Node *)malloc(sizeof(Node));
	root->next = NULL;

	str = (int *)malloc(sizeof(int) * 5001);

	while (fgetc(stdin)) 
	{
		buffer = (int )malloc(sizeof(int) * 5000);
		buffer=str[0];
		curr = root;
		new = (Node *)malloc(sizeof(Node));
		new->x = buffer;
		new->next = NULL;

		while (curr->next != NULL) 
		{
			curr = curr->next;
		}
	
		curr->next = new;
		new->next = NULL;
		str=(int *)malloc(sizeof(int) * 5001);
	}
	free(str);
	return root->next;
}
/* 
 * Goes through the list and checks for ints that are greater than 10, 
 * adds them to a counter and then, divides by the number
 * the total of those numbers . 
 */
void goThrough(Node * root)
{
	int counter=0;
	int total=0;
	int buffer;
	while(root !=NULL)
	{
		buffer=root->x;
		if(buffer>10)
		{
			counter=counter + buffer;
			total++;
		}
		root=root->next;
	}
	printf("%d", counter/total);	
}			

/* Main method that calls the above methods */
int main(void)
{
	Node *root = createlist();
	goThrough(root);
	return 0;
}
