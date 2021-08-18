#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Linked_List_handler.h"
#include "ArrayHandler.h"
#include "Operators.h"
#include "Seperators.h"
#include "LexerTry.h"
#define IDIENTIFIER_YES 	127
#define IDIENTIFIER_NO	 	126
#define INT_NUM 	124
#define FLOAT_NUM	125

int Char_Number ;
extern int Scope_Number;
extern int line;
extern char token[30];


extern Variable *Head;
static int init = 0;

void Array_Handler(char Stack[3][10])
{
	printf("iam in Array handler...........****\n");
	//local variables for calling search functions
	char loc_name[15]="";
	char Loc_DataType[15];
	char Loc_size=0;
	char Loc_GetTocken[15];
	char get_token=0;
	char loc_datatype;
	char loc_vartype=0;
	char loc_init=0;
	char init = 0;
	char flag=0;

	
	Variable *newPtr;/*pointer to declare new node*/
	
	//save data type in local variable
	strcpy(Loc_DataType,Stack[0]);
	printf("%s data type\n",Loc_DataType);
	//save variable name in local variable
	strcpy(Loc_GetTocken,Stack[1]);
	printf("%s Array name\n",Loc_GetTocken);
	//i have for now in array Stack element 0 "data type" element 1 "variable name" element 2 "["
	printf("iam in Array handler\n");
	//get new tocken it should be constant
	get_token=Get_Tocken();
	if(get_token == INT_NUM) /*get new token it should be constant or "]" else -> error */
	{
		//int x[5
		printf("iam in Array handler and found size number\n");
		printf("%s\n",token);		// print the number of the size
		Loc_size=get_token;
		get_token=Get_Tocken();
		if (get_token==CLOSE_ARR)
		{
			//int x[5]
			get_token=Get_Tocken();
			if (get_token==EQUAL)
			{
				//int x[5]=
				printf("equal....\n");
				init=1;
				//get a new token and it should be '{'
				get_token=Get_Tocken();
				printf("new token %s\n",token);
				if (get_token!=OPEN_BRACKET)
				{
					//int x[5]=
					printf("%d: error: invalid initializer\n",line);
					exit(1);		
				}
				else 
				{
					newelement:
					//int x[5]={
					//get a new token and it should be constant
					get_token=Get_Tocken();
					printf("new token %s\n",token);
					if (get_token!=INT_NUM)
					{
						//int x[5]={,,
						printf("Im here\n");
						printf("syntax error in line %d\n",line); 	 
						exit(1);
					}
					else 
					{
						//int x[5]={2
						//get a new token and it should be , or }
						get_token=Get_Tocken();
						printf("new token %s\n",token);
						if (get_token == COMMA )
						{
							goto newelement;
						}
						else if (get_token == CLOSE_BRACKET )
						{
							get_token=Get_Tocken();
							printf("new token %s\n",token);
							if (get_token==SEMI_COMMA)
							{
								flag=1;
							}
							else 
							{
							printf("%d: error: Expected ; \n",line); 	 
							exit(1);
							}
						}
						else 
						{
							printf("syntax error in line %d\n",line); 	 
							exit(1);

						}

					}
				}
			}
			else if (get_token==SEMI_COMMA)
			{
				//int x[5];
				init=0;
				flag=1;
			}
			else if (get_token==COMMA)
			{
				//int x[5],
				printf("flag = 2\n");
				flag=2;
			}
			else 
			{
				printf("syntax error in line %d\n",line); 	 
				exit(1);
			}
		}
		else 
		{
		//error --> int x[5
		printf("%d: error: expected ']' \n",line);
		exit(1);		
		}
	}
	else if (get_token == CLOSE_ARR)
	{
		//int x[]
		get_token=Get_Tocken();
		if (get_token != EQUAL)
		{
		printf("%d: error: array size missing in %s\n",line,Loc_GetTocken);
		exit(1);		
		}
		else 
		{
			//int x[]=
			printf("equal....");
			init=1;
		}
	}
	else 
	{	
		//error ml2ash wla rkam wla ] b3d el [ --> int x[,
		printf("%d: error: expected ']' \n",line);
		exit(1);
	}
	
	
	//search for Array to see if it's redeclared
	int result = search_init(&Head,&Loc_GetTocken,Stack[0],init,1,Loc_size);
	printf("REs =   %d\n",result);
	switch(result){
	 case CONFILCT:
	 
	    printf("%d:  conflicting types for '%s'\n",line,Loc_GetTocken);
		printf("%d: note: previous declaration of '%s' was here",line,Loc_GetTocken); 	 
		exit(1);
		break;
	 case REDECLARED:
	 	 // Error Happens Just Continue Checking
		printf("%d: error: redeclaration of '%s' with no linkage\n",line,Loc_GetTocken);
		printf("%d: note: previous declaration of '%s' was here",line,Loc_GetTocken); 	 
		exit(1);
		break;
	 case NEW_VAR:
		printf("Array handler --> new Array variable\n");
		newPtr = (Variable *) malloc(sizeof(Variable));
		strcpy(newPtr->Name,Loc_GetTocken); //Add the name
		strcpy(newPtr->dataType,Stack[0]); //Add the datatype
		newPtr->Def_Num = line;
		newPtr->scope = Scope_Number;
		newPtr->Arr_Size = Loc_size;
		newPtr->INIT = init;
		push(&Head,&newPtr);
		PrintNodes(&Head);
	 break;
	}

	if(flag==1)//flag = 1 line finished no error return 1
	{
		printf("flag=1\n");
		return 1;
	}
	else if(flag==2)//flag = 2 -> another initialization so call function Array handler again
	{
		newptr:
		printf("flag=2\n");
		char arr[3][10];
		strcpy(arr[0],Loc_DataType);
		get_token=Get_Tocken();
		if(get_token == ASTRICS)
		{
			//int x[],*
			printf("astrics found\n");
			strcpy(arr[1],token);
			Pointer_Handler(&arr);	//call pointer function
		}
		else if(get_token == IDIENTIFIER_YES)
		{
			printf("Identifier found\n");
			strcpy(arr[1],token);
			get_token=Get_Tocken();
			//int x[],y
			if (get_token == OPEN_ARR)
			{
				printf("I reached here %s\n",token);
				//int x[],y[
				strcpy(arr[2],token);
				Array_Handler(&arr);	//call Array function
			}
			else if (get_token == SEMI_COMMA)
			{
				//int x[],y;
				printf("identifier found\n");
				//its identifier call variable handler
			}
			else if (get_token == COMMA)
			{
				goto newptr;

			}
			else 
			{
				printf("syntax error in line %d\n",line); 	 
				exit(1);
			}

			
		}
		else 
		{
			printf("syntax error in line %d\n",line); 	 
			exit(1);
		}
	}
	else 
	{
			printf("syntax error in line %d\n",line); 	 
			exit(1);

	}

}
/*
void main(){
	char *Stack[] = {"flaot","arr1","[","5","]","="};
	ArrayHan(&Stack);
	char *Stack2[] = {"int","arr2","[","0","]","="};
	ArrayHan(&Stack2);
	char *Stack3[] = {"char","arr3","[","10","]","="};
	ArrayHan(&Stack3);
	PrintNodes(&Head);
}*/

