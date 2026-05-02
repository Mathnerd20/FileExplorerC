#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/stat.h>
#include<errno.h>
#include<limits.h>

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
void newf(node *cur, char *name, int load); //create new file
void newd(node *cur, char *name, int load); //create new directory
void initialize(node **cur); //initializes file system
void list(node *cur); //list directory contents.
void Rlist(node *cur); //list directory contents recursively.
void jumpd(node **cur); //change directory
void load(node *cur); //load contents of directory on hard drive into my program

void jumpd(node **cur)
{
    if((*cur)->det == TYPE_FILE)
    {
	printf("Error, can't enter into a file.\n");
	return;
    }
    char dirName[20];
    scanf("%s", dirName);
    if(strcmp(dirName, "..") == 0) //jump into parent
    {
	if((*cur)->up != NULL)
	{
	    *cur = (*cur)->up;
	}
	else
	{
	    printf("Already at top most directory \n");
	}
	return;
    }
    node *temp = *cur;
    temp = temp->in;

    //finding the directory
    while(temp != NULL && strcmp(temp->name, dirName) != 0)
    {
	temp = temp->right;
    }
    if(temp != NULL)
    {
	if((*cur)->det == TYPE_DIR)
	{
	    *cur = temp;
	    load(*cur); //loads the contents of the new directory into the tree.
	}
	else
	{
	    printf("%s is not a directory \n", (*cur)->name);
	}
    }
    else
    {
	printf("Error, directory not found! \n");
    }
}

void load(node *cur)
{
    if(cur->in != NULL)
    {
	return;
    }
    if(cur->det == TYPE_FILE)
    {
	printf("Error, can't load files of a file \n");
	return;
    }
    char path[PATH_MAX];
    getpath(cur, path);
    DIR *d;
    d = opendir(path);
    if(d == NULL)
    {
	return;
    }
    struct dirent *item;
    struct stat stbuf;
    while((item = readdir(d)) != NULL)
    {
	if(strcmp(item->d_name, ".") == 0 || strcmp(item->d_name, "..") == 0)
	{
	    continue;
	}
	char itemPath[PATH_MAX];
	snprintf(itemPath, PATH_MAX, "%s/%s", path, item->d_name);
	stat(itemPath, &stbuf);

	if(S_ISDIR(stbuf.st_mode))
	{
	    newd(cur, item->d_name, 1);
	}
	else
	{
	    newf(cur, item->d_name, 1);
	}
    }
}


void list(node *cur)
{
    if(cur->det == TYPE_FILE)
    {
	printf("Error, can't list a file \n");
	return;
    }
    if(cur->in == NULL)
    {
	printf("Directory Empty \n");
    }
    cur = cur->in;
    while(cur != NULL)
    {
	if(cur->det == TYPE_FILE)
	{
	    printf("%s ", cur->name);
	}
	else
	{
	    printf("\x1B[34m %s \x1B[0m ", cur->name);
	}
	//printf("%s %s\n", (cur->det == TYPE_DIR ? "[DIR] " : "[FILE]"), cur->name);
	cur = cur->right;
    }
    printf("\n");
}

void newf(node *cur, char *name, int load) //if load = 0, it creates an actual file in directory, if 1 then it just makes the virtual file
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

    strcpy(new->name, name);

    if(!load)
    {
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
	    strcpy(new->name, home); //path of home directory copied into name
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

void newd(node *cur, char *name, int load) //new directory
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

	strcpy(new->name, name);

	if(!load)
	{
	    char path[PATH_MAX];
	    getpath(new, path);
	    mkdir(path, 0777);
	}
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
