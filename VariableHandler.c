#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Linked_List_handler.h"
#include "ArrayHandler.h"

#include "VariableHandler.h"
#include "Operators.h"
#include "Seperators.h"
#include "LexerTry.h"
#define IDIENTIFIER_YES 	127
#define IDIENTIFIER_NO	 	126
#define INT_NUM 	124
#define FLOAT_NUM	125

/* function input 
 stack{0} = data type 
 stack{1} = Variable name
 stack{2} = 3rd token
 */
/* Function Cover 
  int x,y[4]={1,3};
  int x=
  int x,
  x= y; 
  x= 5 ;
  x= 5 + 6 ;
*/
 
/*Line_Number  Char_Number from Token Code */
//int Line_Number  = 5;
int Char_Number ;
/*From Scope Code */
extern int Scope_Number;
extern int line;
extern char token[30];
extern Variable *Head;
static int init = 0;

char Variable_Handler(char Stack[3][10])
{
	
	//local variables for calling search functions

	char Loc_DataType[15];
	char loc_Variablename[15];
	char loc_datatype;
	char loc_vartype=0;
	char *get_token;
	char loc_init=0;
	char init = 0;
	char flag=0;
	Variable *newPtr;/*pointer to declare new node*/
	
	//save data type in local variable
	strcpy(Loc_DataType,Stack[0]);
	printf("%s data type\n",Loc_DataType);
	//i have for now in array Stack element 1 "data type" element 2 "variable"
	strcpy(loc_Variablename,Stack[1]);
	printf("iam in variable handler\n");
	char arr[3][10];
	strcpy(arr[0],Loc_DataType);
	strcpy(arr[1],loc_Variablename);
	
		
		if (strcmp (Stack[2],"[")==0 ) //get new tocken if equal "OPEN_ARR " send it to Array Handler 
		{
			
			printf("OPEN_ARR found\n");
			strcpy(arr[2],get_token);
			Array_Handler(&arr); //it's OPEN_ARR call Array_Handler handler
			
		}
		
		else if(strcmp (Stack[2],";")==0 ) //get new tocken if equal "semi comma" line finished set flag by 1
		{
			init=0;
			flag=1;
		}
		else if(strcmp (Stack[2],",")==0 ) //if tocken equal "comma" there is another declaration set flag by 2
		{
			printf("flag = 2\n");
			flag=2;
		}
		else if(strcmp (Stack[2],"=")==0 ) //get new token if equal its init variable
		{
			printf("equal....");
			init=1;
			flag=3;
		}
		else
		{
			printf("syntax error in line %d",line); 	 
			exit(1);
		}
		
	
	 /*Check For Existance Globally*/
	 if(strcmp(Stack[2],"=") == 0)
	 {
		 //printf("init\n");
		 init = 1; 
	 }
	 
	 int result = search_init(&Head,&loc_Variablename,Stack[0],init,0,0);

	 //printf("------------------->REs =   %d\n",result);
	 
		 switch(result)
		 {
		 case CONFILCT:
		 
		    printf("%d:  conflicting types for '%s'\n",line,loc_Variablename);
			printf("%d: note: previous declaration of '%s' was here",line,loc_Variablename); 	 
			exit(1);
			break;
		 case REDECLARED:
		 	 // Error Happens Just Continue Checking
			printf("%d: error: redeclaration of '%s' with no linkage\n",line,loc_Variablename);
			printf("%d: note: previous declaration of '%s' was here",line,loc_Variablename); 	 
			exit(1);
			break;
		 case NEW_VAR:
			newPtr = (Variable *) malloc(sizeof(Variable));
			strcpy(newPtr->Name,Stack[1]); //Add the name
			strcpy(newPtr->dataType,Stack[0]); //Add the datatype
			newPtr->Def_Num = line;
			newPtr->Var_Type = 0;
			newPtr->scope = Scope_Number;
			newPtr->INIT = init;
			printf("VariableHandler-->Add new Variable Name = %s,Type = %s,Scope = %d\n",Stack[1],Stack[0],Scope_Number);
			push(&Head,&newPtr);
			PrintNodes(&Head);
		 break;
			
	    }
	    if(flag==1)//flag = 1 line finished no error return 1
		{
			printf("flag=1 you got ; end of statment \n");
			return 1;
		}
		else if(flag==2)//flag = 2 -> another initialization so call function pointer handler again
		{
			
			printf("flag=2\n");
			char arr2[3][10];
			strcpy(arr2[0],Loc_DataType);
			
		    if(Get_Tocken()== IDIENTIFIER_YES)
			{
				printf("identifier found\n");
				strcpy(arr2[1],token);
				//its identifier call variable handler
				Get_Tocken();
				strcpy(arr2[2],token);
				
			}
		    else
			{
				printf("syntax error in line %d",line); 	 
				exit(1);
				return 0;
			}
			Variable_Handler(&arr2);//function call itself again
				
		}
		else if (flag==3)
		{
			char newtoken ;
			
			AGAIN:
		
			     newtoken = Get_Tocken() ;			   
			if(newtoken == IDIENTIFIER_YES)
			{
				strcpy(loc_Variablename,token);
				printf("variable handler --> token = %s\n",loc_Variablename);
				int result = search(&Head,loc_Variablename,loc_datatype,&loc_vartype,&loc_init);
				
				printf("result = %d\n",result);
				if(result==1)
				{
					printf("i have made serach");
				}
				char arr3[3][10];
			    strcpy(arr3[0],Loc_DataType);
				printf("identifier found\n");
				strcpy(arr3[1],token);
				//its identifier call variable handler
				Get_Tocken();
				strcpy(arr3[2],token);
				Variable_Handler(&arr3);//function call itself again
			}
			
			else if ((newtoken == INT_NUM )|| (newtoken == FLOAT_NUM))
			{
	
			  printf("Number found\n");
			  char res ;
			  res =  Get_Tocken();
		
			  if (res >= 40 && res <=50)
			  {
				  printf("operator found\n %d" , line , token );
				  goto AGAIN;
			  }
			  else if (strcmp (token,";")==0)
			  {
				  printf(" you got ; end of statment \n");
			      return 1;
			  }
			  else 
			  {
				  printf("syntax error in line %d\n",line); 	 
		          exit(1);
		          return 0;
			  }
				  
			}
		
			else
			{
				printf("%d: error incorrect assignment for variable %s\n",line,loc_Variablename);
				exit(1);
			}
			
		}
			
		else
	   {
		printf("syntax error in line %d\n",line); 	 
		exit(1);
		return 0;
	   }
	 
	  /* No Error Happens Just Continue Checking for grammer*/
		
	return 1;
}
