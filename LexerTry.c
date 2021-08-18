#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//include files
#include "LexerTry.h"
#include "NumberHandler.h"	
#include "KeyWord.h"
#include "Operators.h"
#include "Identifier.h"
#include "Seperators.h"
#include "TreeFunction.h"
#include "ValidDataType-final.h"

#define IDIENTIFIER_YES 	127
#define IDIENTIFIER_NO	 	126

#define INT_NUM 	124
#define FLOAT_NUM	125

//externs
extern double NumFloat;
extern long long int Num;	
//extern int Scope_Number=0;
extern int Get_Tocken();

char Search_DataType[10]="";	/*variable to store the data type of variable being search for it*/

//global variables
int line = 1;  //for line number storing --> +1 with each '\n' detected
/*array to detect token*/
char token[30]="";  // with minimum of 30 character for each token
//char *token_ptr = NULL;
//declaring a pointer of type file that will point to the file
FILE *fileptr;	
//pointer to file to handle function "if_operator" only
FILE *fptr;			

int Res;

		 
//function to check for separators

int main(int argc, char *argv[])
{
	int i=0,res;
	char ch;
	fileptr = fopen("ReadThisFile.txt","r");
	while ((ch = fgetc(fileptr)) != EOF)
	{
		if(DivideTokens(ch) == 1){
		res = Validate_Token(token);
		TreeDecesion(res);
		memset(token,0,strlen(token)); }
	}
	fclose(fileptr);
	return 0;
}

int Get_Tocken(char *Ret_Token){
	char ch , res;
	memset(token,0,strlen(token));
	
	while ((ch = fgetc(fileptr)) != EOF)
	{
		if(DivideTokens(ch) == 1){	
		res = Validate_Token(token);
		//TreeDecesion(res);
		//fseek(fileptr,-1,SEEK_CUR );
		return res;
		}
	}
	fseek(fileptr,-1,SEEK_CUR );
	return -1;
	
}

//this function takes a token as a string and validate it
int Validate_Token(char str[])
{

	signed int x;
	printf("new token %s \n",str);		// just print the token
	char flag = 0;
	if((strlen(str) == 1)&&(isalpha(str[0]) == 0))
	{
		x = Is_Separator(str);
		if(x != -1){
		
			return x;
		}
		
		x  = Is_operator(str,&fileptr);
		if(x != -1){
		
			return x;
		}
	}

	x = Is_Keyword(str);
	if(x != -1){
	
	return x;}
	
	else if(is_identifier(str) != IDIENTIFIER_NO){
	;;
	}
				
	else if( (str[0]>='0') && (str[0]<='9') )
		{
			if(GetNumber(str) == INT_NUM)
			{
				printf("integer number= %d\n", Num);
				return INT_NUM;
			}
			else
			{
				printf("float number= %f\n", NumFloat);
				return FLOAT_NUM;
			}
		}
		else{
			printf("Nothing\n");
		}
	

}
//function to divide and get tokens
int DivideTokens(char ch)
{
	if(ch == '\n'){
		line++;
	}
	if((ch!=' ') && (ch!='\n') && (ch!='\t') && (ch!='\0'))   //check if its not space or new line
	{
		/*if char is one of those detect previous token then take it as a separate token*/
		if((ch == '\'')||(ch == '\"')||(ch == '=')||(ch == '+')||(ch == '-')||(ch == '/')||(ch == '*')||(ch == '%')||(ch == ',')||(ch == ';')||(ch == '<')||(ch == '>')||(ch == '}')||(ch == '{')||(ch == '(')||(ch == ')')||(ch == '&')||(ch == '|') || (ch == '!') || (ch == '[') || (ch == ']'))
		{
			/*if token array not empty validate it first then erase*/
			if(strlen(token)!=0)
			{
				fseek(fileptr,-1,SEEK_CUR );
				return 1;
				Validate_Token(token);
				memset(token,0,strlen(token)); 		// this function clears the string (token) after passing it to DetectToken
			}
			/*now take the char as a token alone*/
			strncat(token,&ch,1);
			// this function concatenates the string token with the following character from the code
			return 1;
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
		/*safety condition to make sure that array of token sent to validation is not empty in case of spaces in start of code or multiple spaces in the middle*/
		if(strlen(token)!=0)
		{
			return 1;
			Validate_Token(token);
			memset(token,0,strlen(token)); 		// this function clears the string (token) after passing it to DetectToken
		}
		else;
	}
	return 0;
}