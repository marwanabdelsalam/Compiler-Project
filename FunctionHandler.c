#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "FunctionHandler.h"
#include "LexerTry.h"
#include "ValidDataType-final.h"
#include "Seperators.h"
#include "Identifier.h"
#include "Linked_List_handler.h"
int Function_Line_No = 5;

void Function_Handler(char 	arr[3][10]);
 enum VAR_TYPE{
	VARIABLE = 1,
	FUNCTION,
	ARRAY,
	POINTER,
	DATA_TYPE_ONLY
}  ;
extern int line;
extern char ReturnArray[3][10];
extern Variable *Head;

char paramters[FUNCTION_NAME_MAX][10];
int paramter_count = 0;
/*line  Char_Number from Token Code */
extern int line  ;
 int Char_Number = 0 ;
/*From Scope Code */
extern int Scope_Number ;
Function_dataType *FunctionHead = NULL;
extern char token[30];


static void get_Function_Paramters(Function_dataType **FuncTemp){
	//Data must be datatype identifier , or )
	//get new token
	Variable *newPtr;/*pointer to declare new node*/
	char var_no,res;	
	char Open_Arch = 1;
	char Comma_nums = 0;
	char dataType_num = 0;
	char ENABLE_IMP = 1;
	Scope_Number++;
	(*FuncTemp)->Paramter_Count = 0;
	GET_NEW:
	res = Get_Tocken();
	printf("Function Handler-->Get New Token = %s...%d\n",token,res);
	/*
	if Comma_nums = 1 y3ne feh valid data typede
	mstne , or identifier
	if > 1 y3ne feh 2 valid data type wra b3d
	lw gt , or  id &	Comma_nums = 0 so mkn4 feh datatype error
	*/
	//Check if it datatype
	AGAIN:

	if(res >= 0 && res <= 14)
	{
		//Validte This datatype
			var_no = Data_Type(res,0);
			(*FuncTemp)->Paramter_Count = dataType_num+1;
			if(ENABLE_IMP == 1){
				if(is_identifier(ReturnArray[1]) == IDIENTIFIER_YES){
						newPtr = (Variable *) malloc(sizeof(Variable));
						strcpy(newPtr->Name,ReturnArray[1]); //Add the name
						strcpy(newPtr->dataType,ReturnArray[0]); //Add the datatype
						newPtr->Def_Num = line;
						newPtr->Var_Type = 0;
						newPtr->scope = Scope_Number;
						newPtr->INIT = 0;
						push(&Head,&newPtr);
						PrintNodes(&Head);
				}
				else{
					ENABLE_IMP = 0;
				}
			}
			//if pointer handler
		/*	if(var_no == 4){
				int astrics = 1;
				New_ASTRICS:
				res = Get_Tocken();
				
				if(res == IDIENTIFIER_YES){
					stpcpy(paramters_dataTypes[dataType_num],token);
				}
				else if((strcmp(token,"*")) == 0){
					astrics++;
					goto New_ASTRICS;
				}
				else if((strcmp(token,",")) == 0){
					*FuncTemp->paramters_types[dataType_num++] = 'p'+astrics;
				}
				else{
					printf("error in declaration function '%s'",*FuncTemp->Name);
					exit(1);
				}
			}*/
			//if comma != 0 so it was other datatype--> ERROR
			if(Comma_nums == 0){
				printf("Fun Handler->>DataType = %s   %s	%s,Token = %s\n",ReturnArray[0],ReturnArray[1],ReturnArray[2],token);
				strcpy((*FuncTemp)->paramters_dataTypes[dataType_num++],ReturnArray[0]);
				}
			else{
				printf("%d:%d: expected declaration specifiers or '...' before ')' token",line,Char_Number);
				exit(1);
				}
				//identifier case
				Comma_nums++;
		 if(is_identifier(token) == IDIENTIFIER_YES){	
			if(Comma_nums == 1){
				//store names to save them in case it mplimentation		
				strcpy(paramters[paramter_count++],token);
				}
			else{
				printf("%d:%d: expected declaration specifiers or '...' before ')' token",line,Char_Number);
				exit(1);
				}
			goto GET_NEW;
				}
			else if(strcmp(token,")") == 0){
				Comma_nums--;
				goto CLOSEARCH;	
				}
			else if(strcmp(ReturnArray[2],")") == 0){
				goto CLOSEARCH;	
				}
		else if(strcmp(token,",") == 0){
			goto COMMA_SECTION;
				}
		else{
				printf("%d:%d: error: in function decleration",line,Char_Number);
				exit(1);
				}

			goto GET_NEW;
				}
	else if(res == OPEN_ARCH)
	{
		Open_Arch++;
		goto GET_NEW;
	}
	else if(res == CLOSE_ARCH)
	{
		CLOSEARCH:
		Open_Arch--;
		goto GET_NEW;
	}
	else if(res == COMMA)
	{	
		COMMA_SECTION:
		if(Comma_nums == 1){
			Comma_nums--;
			//save datatype
			//	strcpy(((*FuncTemp)->paramters_dataTypes[para_num++]),ReturnArray[0]);
				}
		else{
			printf("%d:%d: expected declaration specifiers or '...' before ')' token",line,Char_Number);
			exit(1);
				}
		goto GET_NEW;
	}
	else if(res == SEMI_COMMA)
	{
			
		(*FuncTemp)->implemented = 0;
		if(Open_Arch == 0);
		else if(Open_Arch > 0){
			printf("%d:%d: error:  expected ')' before '('  ",line,Char_Number);
			exit(1);
		}
		else{
			printf("%d:%d: error: expected ';' before '('",line,Char_Number);	
			exit(1);
		}
			clear_scoop(&Head);
										Scope_Number--;
		
	}
		else if(res == OPEN_BRACKET){
			
			if(ENABLE_IMP == 0){
				printf("%d:%d: error:  in function '%s' implementation\n",line,Char_Number,(*FuncTemp)->Name);
				exit(1);
			}
			Scope_Number--;
			(*FuncTemp)->implemented = 1;
				if(Comma_nums != 0){
				printf("%d:%d: error:  expected ')' before '('",line,Char_Number);
				exit(1);	
			}
			 if(Open_Arch > 0){
				printf("%d:%d: error:  expected ')' before '('",line,Char_Number);
				exit(1);
					}
		else if(Open_Arch < 0){
			printf("%d:%d: error: expected ';' before '('",line,Char_Number);	
			exit(1);
		}
		else{
			printf("Fun Handler->>Implimented well\n");
			return;
		}
		//if()
		}
	else{
		printf("%d:%d: error: in function decleration");
		exit(1);
	}
	
	printf("Fun Handler->>Implimented well %d\n",(*FuncTemp)->Paramter_Count);
}

void Function_Handler(char 	Stack[3][10]){
	Function_dataType *FuncTemp = (Function_dataType *) malloc(sizeof(Function_dataType));
	printf("i'm in Function Handler Func \n");
	FuncTemp -> scope = Scope_Number;
	FuncTemp -> Def_Num = line;
	strcpy(FuncTemp->returnVal,Stack[0]);
	strcpy(FuncTemp->Name,Stack[1]);
	/*Stack 
	0-->return typedef
	1-->Name
	2-->'('
	so next token is : datatype,identifier,')'
	*/
	int result ;
	/*
	result  0-->No such a name check if it implimentation --<scope  if != 0 --> error else okay
			1-->Name is defiened with same returntype check for the paramters name if it equal no error and not added 
			2-->Name is defiened with other returntype
	*/
	get_Function_Paramters(&FuncTemp);
	result = Function_Search(&FunctionHead,&FuncTemp);
	switch(result){
		case NEW_FUN:
			//ADD new node now
			push_func(&FunctionHead,&FuncTemp);
			break;
		case OLD_FUN_SAME_RETURN:
			//compare parameter of old and new
			break;
		case OLD_FUN_DIFFERNCE_RETURN:
			printf("%d:%d: error: conflicting types for '%s'\n",line,Char_Number,FuncTemp->Name);
			printf("%d:%d:  note: previous declaration of '%s' was here",Function_Line_No,Char_Number,FuncTemp->Name);
			exit(1);
			break;
		case OLD_FUN_DIFFERNCE_PARAMTERS:
			printf("%d:%d: error: conflicting paramters for '%s'\n",line,Char_Number,FuncTemp->Name);
			printf("%d:%d:  note: previous declaration of '%s' was here",Function_Line_No,Char_Number,FuncTemp->Name);
			exit(1);
			break;
		case REDECLARED_FUN:
			printf("%d:%d: error: conflicting declaration for '%s'\n",line,Char_Number,FuncTemp->Name);
			printf("%d:%d:  note: previous declaration of '%s' was here",Function_Line_No,Char_Number,FuncTemp->Name);
			exit(1);
			break;
		case OLD_ONE:
			printf("Same name but no error \n");
			break;
	}

	PrintNodes_fun(&FunctionHead);
	 
		 
	/*check if it is closed or not*/
	
}
