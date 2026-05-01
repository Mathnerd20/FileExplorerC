#include "structs.h"

int main()
{
    printf("Welcome to file explorer program! \n");
    printf("> ");
    node *curr = NULL;
    newd(&curr);
    char cmd[20];
    scanf("%s", cmd);
    while(strcmp(cmd, "quit") != 0)
    {
	if(strcmp(cmd,"list") == 0) //list contents in current directory
	{

	}
	else if(strcmp(cmd,"newf") == 0) //add new file
	{
	    newf(curr);
	}
	else if(strcmp(cmd,"newd") == 0) //add new directory
	{

	}
	else if(strcmp(cmd,"jumpd") == 0) //change to directory in current directory
	{

	}
	else if(strcmp(cmd,"see") == 0) //view contents of file.
	{
	}
	else if(strcmp(cmd,"getinfo") == 0) //give metadata of file.
	{
	}
	printf("> ");
	scanf("%s", cmd);
    }
}
