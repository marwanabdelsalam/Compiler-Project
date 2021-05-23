/*
Author : Marwan Abdelsalam

this program simulate the lexer role

Version : 1.0.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>		//for the strcat function


//declaring a pointer of type file that will point to the file
FILE *fileptr;				

//The path in which the file is to be read from or write on
#define PATH "E://ITI//C//C_Workspace//Compiler Project//codes//"

//this function takes a token as a string and deal with it
void DetectToken(char str[])
{
	printf(" %s \n",str);		// just print the token
}

//this function takes the whole code as a string and detects each token then pass it to function DetectToken to deal with it as a separate string
void DivideTokens(char code[])
{
	char token[30]="";  // with minimum of 30 character for each token
	int i=0;
	for (i=0 ;i< strlen(code)+1 ; i++)   
		{
			if((code[i]!=10) && ((code[i]!=32))&& ((code[i]!='\0')))   // 10 is asci for new line and 32 is asci for space they could be ' ' and '\n'
			{
				strncat(token,&code[i],1);								// this function concatenates the string token with the following character from the code
			}
			else 
			{
				DetectToken(token);
				memset(token,0,strlen(token)); 		// this function clears the string (token) after passing it to DetectToken
			}
		}
}

int main(int argc, char *argv[])
{
	char file[5000]="";
	char code[100];
	int i=0;
	strcat(file,PATH);
	strcat(file,argv[1]);
	fileptr = fopen(file,"r");

	if(fileptr == NULL)						
    {
        printf("Error in reading file!\n");
    }
    else
        printf("File read Successfully !\n");
	
	while ((!feof(fileptr)))
	{
		fscanf(fileptr,"%c",&code[i]);	
		i++;
	}

	DivideTokens(code);
	fclose(fileptr);
}