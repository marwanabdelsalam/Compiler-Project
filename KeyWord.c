#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "KeyWord.h"



char Keyword[32][10]= { "long", "short","signed","unsigned",
						"void","char","int","float","double",
						"volatile","const","static","register","auto","extern", 
						"enum","struct","union", 
						"for","do","while"
						"if","else","switch","case",
						"break","default","continue","return",
						"typedef","goto","sizeof"};

	//function to check for keyword
unsigned int Is_Keyword(char *Token)	
{
	
	int i;
	int Token_Length = strlen(Token);
		
	if ( Token_Length < 2 )
	{
		//printf("not keyword\n");
		return ERROR;
	}
	else 
	{
		for (i=0; i<32; i++)
		{
			if ((strcmp(Keyword[i],Token)) == 0 )
			{
				printf("Keyword\n");	
				return i+1;		// check this
			}
		}
	}

	//printf("not keyword\n");
	return ERROR;
}	
	