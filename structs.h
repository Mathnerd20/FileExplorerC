#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/stat.h>
#include <errno.h>
#include <limits.h>
typedef enum
{
    TYPE_FILE,
    TYPE_DIR
} filetype;

struct item
{
    filetype det;
    char name[100];
    struct item *right;
    struct item *left;
    struct item *up;
    struct item *in;
};
typedef struct item node;
//function prototypes
char* getpath(node *cur, char *path); //gets path of file/directory
void newf(node *cur); //create new file
void newd(node **cur); //create new directory

void list(node **cur)
{
    char path[PATH_MAX];
    if((*cur)->det == TYPE_FILE)
    {
    }
}

void newf(node *cur)
{
    if(cur->det == TYPE_FILE)
    {
	printf("Error, can't create file inside file");
	return;
    }

    node *new; //assumption: the current pointer is always put at the parent directory
    new = malloc(sizeof(node));

    if(cur->in == NULL)
    {
	new->up = cur;
	cur->in = new;
	new->left = NULL;
    }
    else
    {
	cur = cur->in;
	new->up = cur->up;
	while(cur->right != NULL)
	{
	    cur = cur->right;
	}
	cur->right = new;
	new->left = cur;
    }

    printf("Enter name of file: ");
    scanf("%s", new->name);

    new->right = NULL;
    new->det = TYPE_FILE;
    new->in = NULL;

    //check this stuff again, getting path.

    /*cur = new;
    strcpy(path, cur->name);
    while(cur->up != NULL)
    {
	snprintf(path, PATH_MAX, "%s/%s", cur->up->name, path);
	cur = cur->up;
    }*/

    char path[PATH_MAX];
    getpath(new,path);
    FILE *f = fopen(path, "w");
    if(f == NULL)
    {
	printf("Error couldn't create file");
    }
    else
    {
	fclose(f);
    }
}

void newd(node **cur)
{
    if(*cur == NULL) //initialize to home directory
    {
	node *new;
	new = malloc(sizeof(node));
	char *home = getenv("HOME");
	if(home != NULL)
	{
	    strcpy(new->name, home);
	}
	new->left = NULL;
	new->right = NULL;
	new->up = NULL;
	new->det = TYPE_DIR;
	*cur = new;
    }
}

void getpath(node *cur, char *path)
{
    char start[PATH_MAX];
    strcpy(path, cur->name);
    while(cur->up != NULL)
    {
	strcpy(start, path);
	snprintf(path, PATH_MAX, "%s/%s", cur->up->name, start);
	cur = cur->up;
    }
}
