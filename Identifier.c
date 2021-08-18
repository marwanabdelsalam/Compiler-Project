#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Identifier.h"

//function to check for identifiers
char is_identifier(char str[])
{
	int i;
	if (str[0]=='0' || str[0]=='1' || str[0]=='2' || str[0]=='3' || str[0]=='4' || str[0]=='5' || str[0]=='6' || str[0]=='7' || str[0]=='8' || str[0]=='9' || str[0] == '+' || str[0] == '-' || str[0] == '*' || str[0] == '/' || str[0] == ',' || str[0] == ';' || str[0] == '>' || str[0] == '<' || str[0] == '=' || str[0] == '(' || str[0] == ')' || str[0] == '[' || str[0] == ']' || str[0] == '{' || str[0] == '}' || str[0]==',' || str[0]==';')
	{
		printf("ID-->not identifier\n");	
		return IDIENTIFIER_NO;
	}	

	else
	{
		printf("ID-->valid identifier\n");
		return IDIENTIFIER_YES;
	}			
}
