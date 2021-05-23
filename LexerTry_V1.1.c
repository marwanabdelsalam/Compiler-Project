/*
Author : Marwan Abdelsalam

this program simulate the lexer role

Version : 1.1.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>		//for the strcat function
void is_identifier(char *p);
//void parser();
void Validate_Token(char str[]);
void DivideTokens(char code[]);
//global variables
int line = 1;  //for line number storing --> +1 with each '\n' detected
char file[5000]="";
char code[100];
/*array to detect token*/
char token[30]="";  // with minimum of 30 character for each token
//char *token_ptr = NULL;
//declaring a pointer of type file that will point to the file
FILE *fileptr;				

//The path in which the file is to be read from or write on
#define PATH "E://ITI//C//C_Workspace//Compiler Project//codes//"

//this function takes a token as a string and validate it
void Validate_Token(char str[])
{
	printf(" %s \n",str);		// just print the token
	is_identifier(str);
}

//this function takes the whole code as a string and detects each token then pass it to function DetectToken to deal with it as a separate string
void DivideTokens(char code[])
{
	memset(token,0,strlen(token)); 		// this function clears the string (token) after passing it to DetectToken
	int i=0;
	for (i=0 ;i< strlen(code) ;i++)   
	{
		if((code[i]!=' ') &&(code[i]!='\n')&& (code[i]!='\0'))   //check if its not space or new line
		{
			strncat(token,&code[i],1);	// this function concatenates the string token with the following character from the code
			/*if this token is one of the following return it as a token and continue checking from the next element*/
			if((*token == '=')||(*token == '+')||(*token == '-')||(*token == '/')||(*token == '*')||(*token == '%')||(*token == ',')||(*token == ';')||(*token == '<')||(*token == '>')||(*token == '}')||(*token == '{')||(*token == '(')||(*token == ')')||(*token == '&')||(*token == '|')||(*token == '!'))
			{
				Validate_Token(token);
				memset(token,0,strlen(token)); 		// this function clears the string (token) after passing it to DetectToken
			}
			/*else if the following element of a token is not one of the following it do nothing*/
			else if((code[i+1]!='(')&&(code[i+1]!=')')&&(code[i+1]!='=')&&(code[i+1]!='+')&&(code[i+1]!='-')&&(code[i+1]!='/')&&(code[i+1]!='*')&&(code[i+1]!='%')&&(code[i+1]!=',')&&(code[i+1]!='<')&&(code[i+1]!='>')&&(code[i+1]!=';')&&(code[i+1]!='{')&&(code[i+1]!='}')&&(code[i+1]!='&')&&(code[i+1]!='|')&&(code[i+1]!='!')&&(code[i+1]!=' ')&&(code[i+1]!='\n')&&(code[i+1]!='\0'));
			/*if the token is one of the previous condition it enters else--> return the token then erase the token array*/
			else
			{
				//printf(" %s \n",token);
				Validate_Token(token);
				memset(token,0,strlen(token)); 		// this function clears the string (token) after passing it to DetectToken
			}
		}
		else;
	}
}
void is_identifier(char *p)
{
	int i;
	if (*(p+0)=='0' || *(p+0)=='1' || *(p+0)=='2' || *(p+0)=='3' || *(p+0)=='4' || *(p+0)=='5' || *(p+0)=='6' || *(p+0)=='7' || *(p+0)=='8' || *(p+0)=='9' || *(p+0) == '+' || *(p+0) == '-' || *(p+0) == '*' || *(p+0) == '/' || *(p+0) == ',' || *(p+0) == ';' || *(p+0) == '>' || *(p+0) == '<' || *(p+0) == '=' || *(p+0) == '(' || *(p+0) == ')' || *(p+0) == '[' || *(p+0)== ']' || *(p+0) == '{' || *(p+0) == '}')
		printf("not identifier\n");	
		
		//return 0;
	/*for (i=0;i<strlen(str),i++)	
		{
			if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == ',' || str[i] == ';' || str[i] == '>' || str[i] == '<' || str[i] == '=' || str[i] == '(' || str[i] == ')' || str[i] == '[' || str[i] == ']' || str[i] == '{' || str[i] == '}')
				printf("not identifier");
				//return 0;
		}	*/
	else
		printf("valid identifier\n");		
}
//parser function gets token by token from lexer and check if its valid then store in array..
/*void parser(void)
{
	
	int token=0;		//variable to store token return from lexer
	int valid = 0;		//variable to store return of functions
	while ((!feof(fileptr)))
	{
		token = DivideTokens(char code);
		
		valid = is_keyword(token);		//return boolean error state "0/1"
		valid = is_separator(token);	//return boolean error state "0/1"
		valid = is_operator(token);		//return boolean error state "0/1"
		valid = is_number(token);		//return boolean error state "0/1"
		valid = is_identifier(token);	//return boolean error state "0/1"
		
		if(valid == 0)
		{
			//return "error message","line number";
		}
		else
		{
			//store in array
			//array pointer ++;
		}
	}
}
*/
//semantic function used to check grammer and logic and generate error messages due to errors found..
/*void parser()
{
	token_ptr = DivideTokens(code);
	is_identifier(token_ptr);
}*/

int main(int argc, char *argv[])
{
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
	return 0;
}