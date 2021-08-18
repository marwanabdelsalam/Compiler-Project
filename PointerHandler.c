#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Linked_List_handler.h"
#include "PointerHandler.h"
#include "Operators.h"
#include "Seperators.h"
#include "LexerTry.h"

#define IDIENTIFIER_YES 	127
#define IDIENTIFIER_NO	 	126
/*Line_Number  Char_Number from Token Code */
//int Line_Number  = 5;
int Char_Number ;
/*From Scope Code */
extern int Scope_Number;
 
extern int line;
extern char token[30];
extern char Search_DataType[10];
/*void Statement_PointerGramCheck(){
	;;
}*/
Variable *Head = NULL;

static int init = 0;

char Pointer_Handler(char Stack[3][10])
{
	printf("iam in pointer handler...........****\n");
	//local variables for calling search functions
	char loc_name[15]="";
	char Loc_DataType[15];
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
	//i have for now in array Stack element 1 "data type" element 2 "*"
	printf("iam in pointer handler\n");
	//get new tocken it should be identifier
	if(Get_Tocken() == IDIENTIFIER_YES)/*get new token it should be identifier else -> error */
	{
		printf("iam in pointer handler and found name of pointer\n");
		strcpy(Loc_GetTocken,token);
		printf("%s\n",Loc_GetTocken);
		get_token = Get_Tocken();
		if(get_token == EQUAL)//get new token if equal its init pointer
		{
			printf("equal....");
			init=1;
		}
		else if(get_token == SEMI_COMMA)//get new tocken if equal "semi comma" line finished set flag by 1
		{
			init=0;
			flag=1;
		}
		else if(get_token == COMMA)//if tocken equal "comma" there is another declaration set flag by 2
		{
			printf("flag = 2\n");
			flag=2;
		}
		else
		{
			printf("syntax error in line %d",line); 	 
			exit(1);
		}
		//search for pointer to see if it's redeclared
		int result = search_init(&Head,&Loc_GetTocken,Stack[0],init,1,'0');
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
			printf("pointer handler --> new pointer variable\n");
			newPtr = (Variable *) malloc(sizeof(Variable));
			strcpy(newPtr->Name,Loc_GetTocken); //Add the name
			strcpy(newPtr->dataType,Stack[0]); //Add the datatype
			newPtr->Def_Num = line;
			newPtr->scope = Scope_Number;
			newPtr->INIT = init;
			newPtr->Var_Type =2;
			push(&Head,&newPtr);
			PrintNodes(&Head);
		 break;
			
		}
		if(flag==1)//flag = 1 line finished no error return 1
		{
			printf("flag=1\n");
			return 1;
		}
		else if(flag==2)//flag = 2 -> another initialization so call function pointer handler again
		{
			newptr:
			printf("flag=2\n");
			char arr[3][10];
			strcpy(arr[0],Loc_DataType);
			if(Get_Tocken() == ASTRICS)
			{
				printf("astrics found\n");
				strcpy(arr[1],token);
			}
			else if(Loc_GetTocken == IDIENTIFIER_YES)
			{
				printf("identifier found\n");
				//its identifier call variable handler
			}
			else
			{
				printf("syntax error in line %d",line); 	 
				exit(1);
				return 0;
			}
			Pointer_Handler(&arr);//function call itself again
		}
		else if(Get_Tocken() == AND)
		{
			printf("i have found &\n");
			//Loc_GetTocken = Get_Tocken();
			if(Get_Tocken() == IDIENTIFIER_YES)
			{
				strcpy(loc_name,token);
				printf("pointer handler --> token = %s\n",loc_name);
				int result = search(&Head,loc_name,loc_datatype,&loc_vartype,&loc_init);
				//printf("%s",loc_datatype);
				printf("result = %d\n",result);
				if(result==1)
				{
					printf("i have made serach");
					char token10;
					token10 = Get_Tocken();
					if(token10 == SEMI_COMMA)
					{
						printf("iam in pointer handler\n");
						printf("no problem\n");
						return 1;
					}
					else if(token10 == COMMA)
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
					printf("%d: error incorrect assignment for pointer %s\n",line,loc_name);
					exit(1);
				}
			}
			else
			{
				printf("%d: error incorrect assignment for pointer %s\n",line,loc_name);
				exit(1);
			}
		}
		else
		{
			printf("%d:  warning: initialization makes pointer '%s' from  integer without a cast  '%s'\n",line,Loc_GetTocken,token);
		}

	}
	else
	{
		printf("syntax error in line %d\n",line); 	 
		exit(1);
		return 0;
	}
	 
	  /* No Error Happens Just Continue Checking for grammer*/
		// Pointer_Grammer_Check();
	return 1;
}
/*
void main(){
	char *Stack[] = {"flaot","ptr1","="};
	PointerHan(&Stack);
	char *Stack2[] = {"int","ptr2","="};
	PointerHan(&Stack2);
	char *Stack3[] = {"int","ptr3","="};
	PointerHan(&Stack3);
	PrintNodes(&Head);
}
*/
