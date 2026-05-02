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
void getpath(node *cur, char *path); //gets path of file/directory
void newf(node *cur); //create new file
void newd(node *cur); //create new directory
void initialize(node **cur); //initializes file system

void list(node **cur)
{
    char path[PATH_MAX];
    if((*cur)->det == TYPE_FILE)
    {
    }
}

void newf(node *cur) 
{
    if(cur == NULL)
    {
	printf("File system not initialized");
	return;
    }

    if(cur->det == TYPE_FILE)
    {
	printf("Error, can't create file inside file");
	return;
    }

    node *new; //assumption: the current pointer is always put at the parent directory
    new = malloc(sizeof(node));

    if(cur->in == NULL) //empty directory
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

    new->right = NULL;
    new->in = NULL;
    new->det = TYPE_FILE;

    printf("Enter name of file: ");
    scanf("%s", new->name);

    char path[PATH_MAX]; //storing path of file
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

void initialize(node **cur)
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
	new->right = NULL;
	new->in = NULL;
	*cur = new;
	new->det = TYPE_DIR;
    }
    else
    {
	printf("Already initialized");
	return;
    }
}

void newd(node *cur) //new directory
{
    if(cur != NULL)
    {
	if(cur->det == TYPE_FILE)
	{
	    printf("Can't add directory to file");
	    return;
	}

	node *new;
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

	new->right = NULL;
	new->in = NULL;

	new->det = TYPE_DIR;

	printf("Enter name of directory: ");
	scanf("%s", new->name);

	char path[PATH_MAX];
	getpath(new, path);
	mkdir(path, 0777);
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
