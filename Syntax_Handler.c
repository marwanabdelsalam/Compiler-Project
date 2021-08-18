#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Linked_List_handler.h"
#include "Operators.h"
#include "Seperators.h"
#include "LexerTry.h"
#include "Syntax_Handler.h"

#define IDIENTIFIER_YES 	127
#define IDIENTIFIER_NO	 	126

#define INT_NUM 	124
#define FLOAT_NUM	125


#define DOUBLE_QUOTES 	 	 123
#define SINGLE_QUOTE  		 122

static void syntax_variable(char start);
static void syntax_array(void);
/*Line_Number  Char_Number from Token Code */
//int Line_Number  = 5;
int Char_Number ;

extern int Scope_Number;
extern Variable *Head;
extern int line;
extern char token[30];
extern char Search_DataType[10];

extern Function_dataType *FunctionHead;

/*From Scope Code */
extern int Scope_Number;
extern Variable *Head;
extern int line;
extern char token[30];
extern char Search_DataType[10];
int Prm_Num;
void Syntax_Number(char start)
{
	printf("iam in syntax number.....*****\n");
	char loc_name[15]="";
	char Loc_DataType[15]="";
	char loc_datatype[15];
	char loc_vartype=0;	
	char loc_init=0;
	char loc_gettocken = Get_Tocken();
	char loc_gettocken2 = 0;
	switch(loc_gettocken)
	{
		case EQUALEQUAL:
		case NOTEQUAL:
		case LESSTHANOREQUAL:
		case GREATERTHANOREQUAL:
		case NOT:
		case OR:
		case AND:
		case FLIP:
		case GREATERTHAN:
		case LESSTHAN:
			if(Get_Tocken() == IDIENTIFIER_YES)
			{
				strcpy(loc_name,token);
				int result = search(&Head,loc_name,loc_datatype,&loc_vartype,&loc_init);
				if(result == 1)
				{
					loc_gettocken2 = Get_Tocken();
					if(loc_gettocken2 == SEMI_COMMA)
					{
						if(start == 1)//call from parse tree
						{
							return;
						}
						else //call from condition
						{
							printf("line: %d error: expected ')' before '%s' \n",line,token);
							exit(1);
						}	
					}
					else if(loc_gettocken2 == CLOSE_ARCH)
					{
						if(start == 1)//call from parse tree
						{
							printf("line: %d error: expected ';' before '%s' \n",line,token);
							exit(1);							
						}
						else //call from condition
						{
							return;
						}	
					}	
					else
					{
						printf("line: %d error: expected ';' before '%s' \n",line,token);
						exit(1);
					}
				}
				else
				{
					printf("line: %d '%s' undeclared (first use in this function) \n",line,token);
					exit(1);	
				}
			}
			else
			{
				printf("line: %d error: expected ';' before '%s' \n",line,token);
				exit(1);
			}
			break;
		default:
				printf("line: %d  error: lvalue required as left operand of assignment \n",line);
				exit(1);
			break;
	}
}
void Syntax_Pointer(void)
{
	printf("iam in syntax pointer*************\n");
	char loc_name[15]="";
	char Loc_DataType[15]="";
	char loc_gettocken2=0;
	char loc_datatype=0;
	char loc_vartype=0;
	char loc_init=0;
	if(strcmp("*",token) == 0)//the call from Tree function
	{
		printf("iam in * case *************");
		if(Get_Tocken() == IDIENTIFIER_YES)
		{
			strcpy(loc_name,token);/*copy name of identifier in loc variable*/
			int result = search(&Head,loc_name,loc_datatype,&loc_vartype,&loc_init);
				if(result == 1)
				{
					loc_gettocken2 = Get_Tocken();
					switch(loc_gettocken2)
					{
						case PLUSPLUS:
						case MINUSMINUS:
							if(Get_Tocken() == SEMI_COMMA)
								return;
							else
							{
								printf("line: %d error: expected ';' before '%s' \n",line,token);
								exit(1);
							}
							break;
						case EQUAL:
							loc_gettocken2 = Get_Tocken();
							if((loc_gettocken2 == INT_NUM)||(loc_gettocken2 == FLOAT_NUM))
							{
								if(Get_Tocken() == SEMI_COMMA)
									return;
								else
								{
									printf("line: %d error: expected ';' before '%s' \n",line,token);
									exit(1);
								}
							}
							else if(loc_gettocken2 == IDIENTIFIER_YES)
							{
								strcpy(loc_name,token);/*copy name of identifier in loc variable*/
								result = search(&Head,loc_name,loc_datatype,&loc_vartype,&loc_init);
								if(result == 1)
								{
									if(Get_Tocken() == SEMI_COMMA)
									return;
								}
								else
								{
									printf("line: %d '%s' undeclared (first use in this function) \n",line,token);
									exit(1);
								}
							}
							else
							{
								printf("line: %d error: expected ';' before '%s' \n",line,token);
								exit(1);
							}
							break;
							
						default:
							printf("line: %d error: expected ';' before '%s' \n",line,token);
							exit(1);
							break;
						
					}
				}
				else
				{
					printf("line: %d error: expected ';' before '%s' \n",line,token);
					exit(1);
				}
		}
		else
		{
			
		}
	}
	else//the call from syntax_handler function
	{
		printf("iam in syntax pointer case assign*************\n");
		strcpy(Loc_DataType,Search_DataType);/*get data type in local variable*/
		loc_gettocken2 = Get_Tocken();
		if(loc_gettocken2 == EQUAL)
		{
			if(Get_Tocken() == AND)
			{
				if(Get_Tocken() == IDIENTIFIER_YES)
				{
					strcpy(loc_name,token);/*copy name of identifier in loc variable*/
					int result = search(&Head,loc_name,loc_datatype,&loc_vartype,&loc_init);
						if(result == 1)
						{
							if(strcmp(Loc_DataType,Search_DataType) != 0)//if data types of the assignment to te pointer not the same
							{
								printf("line: %d warning: assignment from incompatible pointer type\n",line);
							}
							
							if(Get_Tocken() == SEMI_COMMA)
								return;
							else
							{
								printf("line: %d error: expected ';' before '%s' \n",line,token);
								exit(1);
							}
						}
						else
						{
							printf("line: %d '%s' undeclared (first use in this function) \n",line,token);
							exit(1);
						}
				}
				else
				{
					printf("line: %d   error: lvalue required as unary '&' operand \n",line);
					exit(1);
				}
			}
			else
			{
				printf("line: %d warning: assignment makes pointer from integer without a cast\n",line);
			}
		}	
		else if(loc_gettocken2 == SEMI_COMMA)
		{
			return;
		}
		else
		{
			printf("line: %d error: expected ';' before '%s' \n",line,token);
			exit(1);
		}
	}
	return;
}

void Syntax_Handler(char start)
{
	printf("iam in Syntax handler...........****\n");
	//local variables for calling search functions
	char loc_name[15]="";
	char Loc_GetTocken[15]="";
	char get_token=0;
	char loc_datatype=0;
	char loc_vartype=0;
	char loc_init=0;
	//char flag=0;
	//save name in local variable
	strcpy(loc_name,token);
	int result = search(&Head,loc_name,loc_datatype,&loc_vartype,&loc_init);
	//printf("%s",loc_datatype);
	printf("result = %d\n",result);
	if(result == 0)
	{
		syntax_function();
		//printf("line: %d error: '%s' undeclared (first use in this function)\n",line,loc_name);
		//exit(1);
	}
	printf("vartype = %d\n",loc_vartype);
	if(loc_vartype==0)
	{
		syntax_variable(start);
	}
	else if(loc_vartype==1)
	{
		syntax_array();
	}
	else if(loc_vartype==2)
	{
		Syntax_Pointer();
	}
	/*else if(loc_vartype==3)
	{
		//call syntax_function
		syntax_function();
	}*/
	else
		return;
}

static void syntax_variable(char start)
{
	char loc_name[15]="";
	char Loc_DataType[15]="";
	char loc_gettocken = Get_Tocken();
	char loc_gettocken2=0;
	char loc_datatype=0;
	char loc_vartype=0;
	char loc_init=0;
	if((loc_gettocken >= 40)&&(loc_gettocken <= 65))
	{
		switch(loc_gettocken)
		{
			case PLUSPLUS:
			case MINUSMINUS:
				if(Get_Tocken() != SEMI_COMMA)
				{
					printf("line: %d error: expected ';' before '%s' \n",line,token);
					exit(1);
				}
				break;
			case OR:
			case AND:
			case FLIP:
			case NOT:
			case OREQUAL:
			case ANDEQUAL:
			case NOTEQUAL:
				strcpy(Loc_DataType,Search_DataType);
				if((strcmp(Loc_DataType,"F") == 0)|| (strcmp(Loc_DataType,"D") == 0))
				{
					
					printf("line: %d error: invalid operands to binary '%s' \n",line,token);
					exit(1);
				}
				else/*after bit wise operator should be int num or identifier*/
				{
					char loc_gettocken2 = Get_Tocken();
					printf("%d\n",loc_gettocken2);
					if(loc_gettocken2 == INT_NUM)
					{
						if(Get_Tocken() != SEMI_COMMA) 
						{
							printf("line: %d error: expected expression before ';' token \n",line);
							exit(1);
						}
						else 
							return;
					}
					else if(loc_gettocken2 == FLOAT_NUM)
					{
						printf("line: %d error: invalid operands to binary '%s' \n",line,token);
						exit(1);
					}
					else if(loc_gettocken2 == IDIENTIFIER_YES)
					{
						strcpy(loc_name,token);
						int result = search(&Head,loc_name,loc_datatype,&loc_vartype,&loc_init);
						if(result == 1)
						{
							if(Get_Tocken() == SEMI_COMMA)
								return;
							else
							{
								printf("line: %d error: expected ';' before '%s' \n",line,token);
								exit(1);
							}
						}
						else
						{
							printf("line: %d '%s' undeclared (first use in this function) \n",line,token);
							exit(1);
						}
					}
					else
					{
						printf(" line: %d error: expected ';' before '%s' \n",line,token);
						exit(1);
					}
				}
				break;

			default://for other cases rather than the cases above..
				loc_gettocken2 = Get_Tocken();
				if(loc_gettocken2 == SEMI_COMMA)
				{
					printf("line: %d error: expected expression before ';' token\n",line);
					exit(1);
				}
				else if(loc_gettocken2 == IDIENTIFIER_YES)
				{
					Syntax_Handler(start);/*call syntax_handler again to continue dealing with the rest of line*/
				}
				else if((loc_gettocken2 == INT_NUM)||(loc_gettocken2 == FLOAT_NUM))
				{
					loc_gettocken2 = Get_Tocken();
					if(loc_gettocken2 == SEMI_COMMA)
					{
						if(start == 1)//call from tree function
							return;
						else //call from condition
						{
							printf("line: %d error: expected ')' before '%s' \n",line,token);
							exit(1);
						}	
					}	
					else if(loc_gettocken2 == COMMA)
					{
						if(start != 1)
						{
							printf("line: %d error: expected ';' before '%s' \n",line,token);
							exit(1);
						}
						if(Get_Tocken() == IDIENTIFIER_YES)
							Syntax_Handler(start);/*call syntax_handler again to continue dealing with the rest of line*/
						else
						{
							printf("line: %d error: expected ';' before '%s' \n",line,token);
							exit(1);
						}
					}
					else if(loc_gettocken2 == CLOSE_ARCH)
					{
						if(start == 1)//call from tree function
						{
							printf("line: %d error: expected ';' before '%s' \n",line,token);
							exit(1);
						}
						else //call from condition
						{
							return;
						}	
					}	
					else
					{
						printf("line: %d error: expected ';' before '%s' \n",line,token);
						exit(1);
					}					
				}
				else if(loc_gettocken2 == ASTRICS)
				{
					//call syntax_pointer
				}
				else
				{
					printf("line: %d error: expected ';' before '%s' \n",line,token);
					exit(1);
				}
				break;
		}
	}
	else if(loc_gettocken == SEMI_COMMA)
	{
		return;
	}
	else
	{
		printf("line: %d error: expected ';' before '%s' \n",line,token);
		exit(1);
	}
	return;
}

static void syntax_array(void)
{
	
	printf("iam in syntax Array *************\n");
	char loc_name[15]="";
	char Loc_DataType[15]="";
	char loc_gettocken2=0;
	char loc_datatype=0;
	char loc_vartype=0;
	char loc_init=0;

		//loc_gettocken2 = Get_Tocken();
		if(Get_Tocken() == OPEN_ARR)
		{
			//x[
			loc_gettocken2 = Get_Tocken();
			if (loc_gettocken2==INT_NUM)
			{
				check:
				//x[5
				//loc_gettocken2 = Get_Tocken();
				if (Get_Tocken()==CLOSE_ARR)
				{
					//x[5]
					loc_gettocken2 = Get_Tocken();
					if (loc_gettocken2==SEMI_COMMA)
					{
						//x[5];
						return;
					}
					else if (loc_gettocken2==EQUAL)
					{
						//x[5]=
						loc_gettocken2 = Get_Tocken();
						if (loc_gettocken2==INT_NUM)
						{
							//x[5]=2
							if (Get_Tocken()!=SEMI_COMMA)
							{
								//x[5]=2,,
								printf("line: %d error: expected ';' before '%s' \n",line,token);
								exit(1);
							}
							else 
							{
								//x[5]=2;
								return;
							}
						}
						else if (loc_gettocken2==IDIENTIFIER_YES)
						{
							//x[5]=y
							strcpy(loc_name,token);/*copy name of identifier in loc variable*/
					       int result = search(&Head,loc_name,loc_datatype,&loc_vartype,&loc_init);
						   	if(result == 1)
							{
								if(Get_Tocken() == SEMI_COMMA)
									return;
								else
								{
									printf("line: %d error: expected ';' before '%s' \n",line,token);
									exit(1);
								}

							}
							else
							{
							printf("line: %d '%s' undeclared (first use in this function) \n",line,token);
							exit(1);
							}
						}
						else 
						{
							//x[5]=,,
							printf("syntax error in line %d\n",line); 
							exit(1);

						}

					}
					else
					{
					//x[5],,
					printf("syntax error in line %d\n",line); 
					exit(1);

					}
					
				}
				else 
				{
					//x[5,,
					printf("syntax error in line %d\n",line); 
					exit(1);

				}
			}
			else if (loc_gettocken2==IDIENTIFIER_YES)
			{
				//x[y
				strcpy(loc_name,token);/*copy name of identifier in loc variable*/
				int result = search(&Head,loc_name,loc_datatype,&loc_vartype,&loc_init);
				printf("result = %d \n",result);
				if(result == 1)
				{
					goto check;
					/*if(Get_Tocken() == SEMI_COMMA)
					{
						return;
					}
					else
					{
						printf("line: %d error: expected ';' before '%s' \n",line,token);
						exit(1);
					}*/

				}
				else
				{
					printf("line: %d '%s' undeclared (first use in this function) \n",line,token);
					exit(1);
				}

			}
			else 
			{
				//x[,,
				printf("syntax error in line %d\n",line); 
				exit(1);
			}

		}
		else 
		{
			//x + anything except [
			printf("syntax error in line %d\n",line); 
			exit(1);
			
		}
}

static void Check_Parameters (int P_Counter, char *Func_Name)
{
	if (P_Counter < Prm_Num)
		printf(" error: too few arguments to function '%s' ", Func_Name);
	
	else if (P_Counter > Prm_Num)
		printf(" error: too many arguments to function '%s' ", Func_Name);
	
	else if (P_Counter == Prm_Num)
		return;
}

void syntax_function(void)
{
	printf("iam in Syntax Function...........****\n");

	char loc_datatype=0;
	char loc_vartype=0;
	char loc_init=0;
	
	char *Func_Name = token ;
	Prm_Num = Function_Search_Name(&FunctionHead,Func_Name); // Func (x,5,*y) // Func() // Func(,) Func (5,)
	
	if (-1 == Prm_Num)
		printf("error: Undeclerated function %s", Func_Name);
	
	else 
	{
		//int Counter=0;
		char Token = Get_Tocken();
		int P_Counter=0;
		if (Token == OPEN_ARCH)
		{
			Token = Get_Tocken();
			Parameters:
			switch (Token)
			{	
				case INT_NUM:
				case FLOAT_NUM: 
					{
						P_Counter++;
						//Syntax_Number(2);
						Token = Get_Tocken();
					}
					break;
				
				case IDIENTIFIER_YES: // Valid: Func ( x=5, 2);
					{
						P_Counter++;
						char Found = search(&Head,token,loc_datatype,&loc_vartype,&loc_init);
						
						if (Found == 1)
							Token = Get_Tocken();
						else 
							printf(" error: '%s' undeclared (first use in this function)", token);
					}
					break;
					
				case ASTRICS: 
					{
						P_Counter++;
						Token = Get_Tocken();
						
						if (Token == IDIENTIFIER_YES)
						{
							char Found = search(&Head,token,loc_datatype,&loc_vartype,&loc_init);
							
							if (Found == 1)
								Token = Get_Tocken();
							else 
								printf(" error: '%s' undeclared (first use in this function)", token);
						}
						else
							printf(" error: invalid type argument of unary '*'");	
					}
				break;
				
				case AND: 
					{
						P_Counter++;
						Token = Get_Tocken();
						
						if (Token == IDIENTIFIER_YES)
						{
							char Found = search(&Head,token,loc_datatype,&loc_vartype,&loc_init);
							
							if (Found == 1)
								Token = Get_Tocken();
							else 
								printf(" error: '%s' undeclared (first use in this function)", token);
						}
						else
							printf(" error: invalid type argument of unary '&'");	
					}
				break;
				
				case SINGLE_QUOTE:  // character
					{
						do
						{	
							Token = Get_Tocken();
						}
						while (SINGLE_QUOTE != Token);
						
						P_Counter++;
						Token = Get_Tocken();
					}
				break;
				
				case DOUBLE_QUOTES: // String
					{
						do
						{	
							Token = Get_Tocken();
						}
						while (DOUBLE_QUOTES != Token);
						
						P_Counter++;
						Token = Get_Tocken();
					}
				break;

				case COMMA: 
					{
						printf(" error: expected expression before ',' Token");
					}
					break;
					
				default: break;
				
			}
			
			if (Token == CLOSE_ARCH)
				Check_Parameters (P_Counter, Func_Name);
				
			else if (Token == COMMA)
			{
				Token = Get_Tocken();
				if (Token == CLOSE_ARCH)
					printf("error: expected expression before ')' Token");
				
				else	
					goto Parameters;
			}
		}
		else if (Token == SEMI_COMMA){
		return;}
		else{
			printf("error: expected  ';'\n");
			exit(1);}
	}
	
}


