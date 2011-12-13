#include	<stdio.h>
#include	<ctype.h>
#include	<stdlib.h>
#include	<string.h>

typedef struct node 
{
	char cha;
	struct node *next;
} Node;

Node *createlist(void)
{

	Node	*root;
	Node	*curr;

	Node	*new;
	char	*str, buffer;

	root = (Node *)malloc(sizeof(Node));
	root->next = NULL;

	str = (char *)malloc(sizeof(char) * 5001);

	while (fgets(str, 5000, stdin)) 
	{
		buffer = (char )malloc(sizeof(char) * 1);
		buffer=str[0];
		curr = root;
		new = (Node *)malloc(sizeof(Node));
		new->cha = buffer;
		new->next = NULL;

		while (curr->next != NULL) 
		{
			curr = curr->next;
		}
	
		curr->next = new;
		new->next = NULL;
		str=(char *)malloc(sizeof(char) * 5001);
	}
	free(str);
	return root->next;
}

void print(Node * root)
{
	char buffer;
	while (root !=NULL) 
	{
		buffer=root->cha;
		printf("%c", root->cha);
		char * vowels="aeiou";
		while(*vowels!='\0')
		{
			if (tolower(buffer)==*vowels)
			{
				printf("*");
				break;
			}
			vowels++;
		}
		root = root->next;
	}
}

int main(void)
{

	Node *root = createlist();
	print(root);
	return 0;

}
