/*
Author : Marwan Abdelsalam

Description : this program simulate the lexer role

Version : 1.0.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>		//for the strcat function
void is_identifier(char *p);
//void parser();
void Validate_Token(char str[]);
void DivideTokens(char ch);
//global variables
int line = 1;  //for line number storing --> +1 with each '\n' detected
/*array to detect token*/
char token[30]="";  // with minimum of 30 character for each token
//char *token_ptr = NULL;
//declaring a pointer of type file that will point to the file
FILE *fileptr;				

//The path in which the file is to be read from or write on
#define PATH "C://Users//engkh//Desktop//compiler project//New folder//"

//this function takes a token as a string and validate it
void Validate_Token(char str[])
{
	printf(" %s \n",str);		// just print the token
	is_identifier(str);
}

void DivideTokens(char ch)
{
	if((ch!=' ') &&(ch!='\n')&& (ch!='\t')&& (ch!='\0'))   //check if its not space or new line
	{	
		/*if char is one of those detect previous token then take it as a separate token*/
		if((ch == '=')||(ch == '+')||(ch == '-')||(ch == '/')||(ch == '*')||(ch == '%')||(ch == ',')||(ch == ';')||(ch == '<')||(ch == '>')||(ch == '}')||(ch == '{')||(ch == '(')||(ch == ')')||(ch == '&')||(ch == '|')||(ch == '!'))
		{
			/*if token array not empty validate it first then erase*/
			if(strlen(token)!=0)
			{
				Validate_Token(token);
				memset(token,0,strlen(token)); 		// this function clears the string (token) after passing it to DetectToken
			}
			/*now take the char as a token alone*/
			strncat(token,&ch,1);				// this function concatenates the string token with the following character from the code
			Validate_Token(token);
			memset(token,0,strlen(token)); 		// this function clears the string (token) after passing it to DetectToken
		}
		/*if its not a special char continue and concatinate with token array*/
		else
		{
			strncat(token,&ch,1);
		}
	}
	/*if a space or \n or \t encountered validate the token array and erase*/
	else
	{
		if(strlen(token)!=0)
		{
			Validate_Token(token);
			memset(token,0,strlen(token)); 		// this function clears the string (token) after passing it to DetectToken
		}
		else;
	}
}
void is_identifier(char str[])
{
	int i;
	if (str[0]=='0' || str[0]=='1' || str[0]=='2' || str[0]=='3' || str[0]=='4' || str[0]=='5' || str[0]=='6' || str[0]=='7' || str[0]=='8' || str[0]=='9' || str[0] == '+' || str[0] == '-' || str[0] == '*' || str[0] == '/' || str[0] == ',' || str[0] == ';' || str[0] == '>' || str[0] == '<' || str[0] == '=' || str[0] == '(' || str[0] == ')' || str[0] == '[' || str[0] == ']' || str[0] == '{' || str[0] == '}')
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
	char ch;
	fileptr = fopen("ReadThisFile.txt","r");
	while ((ch = fgetc(fileptr)) != EOF)
	{
		DivideTokens(ch);
	}
	fclose(fileptr);
	return 0;
}


