#include "structs.h"

int main()
{
    printf("Welcome to file explorer program! Type 'help' for help and 'quit' to quit \n");
    printf("> ");
    node *curr = NULL;
    initialize(&curr);
    load(curr);
    char cmd[20];
    scanf("%s", cmd);
    while(strcmp(cmd, "quit") != 0)
    {
	char name[20];
	if(strcmp(cmd,"list") == 0) //list contents in current directory
	{
	    list(curr);
	}
	else if(strcmp(cmd,"newf") == 0) //add new file
	{
	    scanf("%s", name);
	    newf(curr, name, 0);
	}
	else if(strcmp(cmd,"newd") == 0) //add new directory
	{
	    scanf("%s", name);
	    newd(curr, name, 0);
	}
	else if(strcmp(cmd,"jumpd") == 0) //change to directory in current directory
	{
	    jumpd(&curr);
	}
	else if(strcmp(cmd,"whereami") == 0) //print current directory
	{
	    whereami(curr);
	}
	else if(strcmp(cmd,"rm") == 0) //remove file or emptry directory
	{
	    rm(curr);
	}
	else if(strcmp(cmd,"see") == 0) //view contents of file.
	{
	    see(curr);
	}
	else if(strcmp(cmd,"getinfo") == 0) //give metadata of file.
	{
	    getinfo(curr);
	}
	else if(strcmp(cmd,"help") == 0) //Give list of commands
	{
	    printf("Avaliable functions are \n whereami - print current working directory \n newf - Add newfile to current directory \n newd - Add new directory to current directory \n jumpd - change directory \n list - list all contents of current directory \n getinfo - provide info on file \n see - view contents of file \n rm - to delete a file or empty directory \n quit - to quit the program \n"); 
	}
	else
	{
	    printf("Invalid command ! \n");
	}
	printf("> ");
	scanf("%s", cmd);
    }
}
