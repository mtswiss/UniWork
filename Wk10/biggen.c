Node *biggen(Node *start, int val)
{
	Node * root, * new, * current;
	root=(Node *)malloc(sizeof(Node));
	current=root;
	while(start!=NULL)
	{
		new=(Node *)malloc(sizeof(Node));
		new->val=(start->val)+val;
		current->next=new;
		start=start->next;
	}
	return root->next;
}