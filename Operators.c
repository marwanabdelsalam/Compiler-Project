#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Linked_List_handler.h"
#include "Operators.h"
//function to check for operators
#define ERROR	-1
#define SINGLE_OPERATORS	13

unsigned int Is_operator(char *Token ,FILE **fptr)
{
	char i;
	char flag=0;
	char ch = '+' ;
	
	char op[] = {'+','-','*','/','>',
				 '<','=','%','!','|',
				 '&','~',':','?'
				};   
		for (i=0; i <= SINGLE_OPERATORS ; i++)
		{
			if (op[i] == Token[0])
			{
				break; 
			}
				
			else
			{
				
			}
				
		}
		if(i > SINGLE_OPERATORS){
		return ERROR;}
	i+=40;
	do{
			ch = fgetc(*fptr);
			switch (Token[0])
			{
			//if current token is one of those cases
			case '=' :
			if (ch == '=')/*if next token == '='*/
			{
				printf ("input %c %c is EQUAL '=='||'!='||'<='||'>='||'/=' operator \n", Token[i],ch);
				return SINGLE_OPERATORS+41;
				
			}
			else if(ch == ' ');/*if next token == ' ' do nothing*/
			else /*its a single operator return the cursor and back*/
				{
					printf ("input %c %c is Assign'=' operator \n", Token[i],ch);
					fseek(*fptr,-1, SEEK_CUR );	/*return cursor by 1*/
					return i;
				}
				break; 
			case '!' :
				if (ch == '=')/*if next token == '='*/
			{
				printf ("input %c %c is EQUAL '=='||'!='||'<='||'>='||'/=' operator \n", Token[i],ch);
				return SINGLE_OPERATORS+42;
				
				
			}
			else if(ch == ' ');/*if next token == ' ' do nothing*/
			else /*its a single operator return the cursor and back*/
				{
					printf ("input %c %c is Assign'=' operator \n", Token[i],ch);
					fseek(*fptr,-1, SEEK_CUR );	/*return cursor by 1*/
					return i;
				}
				break; 
			case '<' :
				if (ch == '=')/*if next token == '='*/
			{
				printf ("input %c %c is EQUAL '=='||'!='||'<='||'>='||'/=' operator \n", Token[i],ch);
				return SINGLE_OPERATORS+43;
				
				
			}
			else if(ch == ' ');/*if next token == ' ' do nothing*/
			else /*its a single operator return the cursor and back*/
				{
					printf ("input %c %c is Assign'=' operator \n", Token[i],ch);
					fseek(*fptr,-1, SEEK_CUR );	/*return cursor by 1*/
					return i;
				}
				break; 
			case '>' :
				if (ch == '=')/*if next token == '='*/
			{
				printf ("input %c %c is EQUAL '=='||'!='||'<='||'>='||'/=' operator \n", Token[i],ch);
				return SINGLE_OPERATORS+44;
				
				
			}
			else if(ch == ' ');/*if next token == ' ' do nothing*/
			else /*its a single operator return the cursor and back*/
				{
					printf ("input %c %c is Assign '=' operator \n", Token[i],ch);
					fseek(*fptr,-1, SEEK_CUR );	/*return cursor by 1*/
					return i;
				}
				break; 
			case '/' :
					if (ch == '=')/*if next token == '='*/
			{
				printf ("input %c %c is EQUAL '=='||'!='||'<='||'>='||'/=' operator \n", Token[i],ch);
				return SINGLE_OPERATORS+45;
				
				
			}
			else if(ch == ' ');/*if next token == ' ' do nothing*/
			else /*its a single operator return the cursor and back*/
				{
					printf ("input %c %c is Assign'=' operator \n", Token[i],ch);
					fseek(*fptr,-1, SEEK_CUR );	/*return cursor by 1*/
					return i;
				}
				break; 
			
			case '*' :
					if (ch == '=')/*if next token == '='*/
			{
				printf ("input %c %c is EQUAL '=='||'!='||'<='||'>='||'/=' operator \n", Token[i],ch);
				return SINGLE_OPERATORS+46;
				
				
			}
			else if(ch == ' ');/*if next token == ' ' do nothing*/
			else /*its a single operator return the cursor and back*/
				{
					printf ("input %c %c is Assign'=' operator \n", Token[i],ch);
					fseek(*fptr,-1, SEEK_CUR );	/*return cursor by 1*/
					return i;
				}
				break; 
				
			case '|' :
			
					if (ch == '=')/*if next token == '='*/
			{
				printf ("input %c %c is EQUAL '=='||'!='||'<='||'>='||'/=' operator \n", Token[i],ch);
				return SINGLE_OPERATORS+47;
				
				
			}
			else if(ch == ' ');/*if next token == ' ' do nothing*/
			else /*its a single operator return the cursor and back*/
				{
					printf ("input %c %c is Assign'=' operator \n", Token[i],ch);
					fseek(*fptr,-1, SEEK_CUR );	/*return cursor by 1*/
					return i;
				}
				break; ;
			case '&' :
			
					if (ch == '=')/*if next token == '='*/
			{
				printf ("input %c %c is EQUAL '=='||'!='||'<='||'>='||'/=' operator \n", Token[i],ch);
				return SINGLE_OPERATORS+48;
				
				
			}
			else if(ch == ' ');/*if next token == ' ' do nothing*/
			else /*its a single operator return the cursor and back*/
				{
					printf ("input %c %c is Assign'=' operator \n", Token[i],ch);
					fseek(*fptr,-1, SEEK_CUR );	/*return cursor by 1*/
					return i;
				}
			break;
			//if current token is == '+'
			case '+' :
				if (ch == '+')
			{
				printf ("input %c %c is  '++' plus plus  operator \n", Token[i],ch);
				return SINGLE_OPERATORS+49; 
			}
				else if(ch == '=')/*if next token == '='*/
				{
					printf ("input %c %c is plus '+=' operator \n", Token[i],ch);
					return SINGLE_OPERATORS+50; 	
				}
				else if(ch == ' ');/*if next token == ' ' do nothing*/
				else/*its a single operator return the cursor and back*/
				{
					printf ("input %c %c is Assign'+' operator \n", Token[i],ch);
					fseek(*fptr,-1, SEEK_CUR ); /*return cursor by 1*/
					return i;
				}
				break; 
			//if current token is == '+'
			case '-' :
				if (ch == '-')
			{
				printf ("input %c %c is '--' minus minus operator \n", Token[i],ch);
				return SINGLE_OPERATORS+51;
			}
				else if(ch == '=')/*if next token == '='*/
				{
					printf ("input %c %c is minus '-=' operator \n", Token[i],ch);
					return SINGLE_OPERATORS+52; 
				}
				else if(ch == ' ');/*if next token == ' ' do nothing*/
				else/*its a single operator return the cursor and back*/
				{
					printf ("input %c %c is Assign'-' operator \n", Token[i],ch);
					fseek(*fptr,-1, SEEK_CUR ); /*return cursor by 1*/
					return i;
				}
				break; 

			default :
				//printf("input %c %c is not double operator \n", op[i],ch);
				fseek(*fptr,-1, SEEK_CUR ); /*return cursor by 1*/
				return i;
				break; 

		}
	}
	while(1);
}