#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct file
{
    int info;
    char name[20];
    int det; //if det = 0, its a file, det = 1, it is directory
    struct file *right; //double linked list
    struct file *left;
    struct file *in;
    struct file *up;
};
typedef struct file item;

item *add(item **root, char a[20])
{
    item *new;
    new = malloc(sizeof(item));
    new->name = strcpy(new->name, a);
    if(*root == NULL) //first file in directory
    {
	*root = new;
	new->right = NULL;
	new->left = NULL; 
	return new;
    }
    item *tmp = *root;
    while(tmp->right != NULL)
    {
	tmp = (tmp)->right;
    }
    (tmp)->right = new;
    new->left = tmp;
    new->right = NULL;
    new->in = NULL;
    new->up = NULL;
    if((*root)->det == 1)
    {
	new->up = *root;
    }
    return new;
}

void newFile(item **root)
{
    item *k;
    char a[20];
    printf("Enter name of Folder to be added: ");
    scanf("%s", a);
    if((*root)->det == 1)
    {
	k = add(&((*root)->in), a);
    }
    else
    {
	k = add(root);
    }
    k->det = 0;
}

void newDir(item **root)
{
    item *k;
    char a[20];
    printf("Enter name of File to be added: ");
    scanf("%s", a);
    if((*root)->det == 1)
    {
	k = add(&((*root)->in));
    }
    else
    {
	k = add(root);
    }
    k->det = 1;
}

item *cd(item *root)
{
    char fld[20];
    printf("Enter folder name: ");
    scanf("%s", fld);
    int found = 0;
    while(strcmp((root)->name,fld) != 0 && root->next != NULL)
    {
	root = root->next;
	if(strcmp((root)->name,fld) == 0)
	{
	    found = 1;
	}
    }
    if(found == 1)
    {
	return root;
    }
    return NULL;
}
