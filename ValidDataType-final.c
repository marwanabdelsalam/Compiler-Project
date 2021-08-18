#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "STD_TYPES.h"
#include "Identifier.h"
#include "LexerTry.h"
#include "ValidDataType-final.h"
#include "VariableHandler.h"
#include "PointerHandler.h"
#include "FunctionHandler.h"
#include "ArrayHandler.h"
//void Pointer_Handler(char 	arr[3][10]);

//void Array_Handler(char 	arr[3][10]);

//void Function_Handler(char 	arr[3][10]);


 enum VAR_TYPE{
	VARIABLE = 1,
	FUNCTION,
	ARRAY,
	POINTER,
	DATA_TYPE_ONLY
}  ;
extern char token[30];
typedef enum Kewyword 
{
	   ERROR =	-1,
	   
	   LONG  = 	0,
	   SHORT = 	1,
	  SIGNED = 	2, 
	UNSIGNED =  3,
	
		VOID =	4,
		CHAR = 	5,
		 INT = 	6,
	   FLOAT = 	7,
	  DOUBLE = 	8,
	  
	VOLATILE =  10,
	   CONST =	11,
	  STATIC = 	12,
	REGISTER =	13,
	    AUTO = 	14,
	  EXTERN = 	15, 
	
	/*	
	
		ENUM = 	15,
	  STRUCT = 	16,
	   UNION = 	17,
	   
		 FOR =  18,
		  DO =  19,
	   WHILE =  20,
	   
		  IF =	21,
	    ELSE =	22,
	  SWITCH = 	23,
	    CASE = 	24,
	   
	   BREAK = 	25,
	 DEFAULT = 	26,
	CONTINUE = 	27,
	  RETURN = 	28,
	  
	 TYPEDEF =	29,
		GOTO =	30,
	  SIZEOF =	31
	  
	*/
	   
} KEYWORD;

char DataType[10][8]= {"long", "short","signed","unsigned",
						"void","char","int","float","double", "BLANK"};


char ReturnArray[3][10]={'\0'};		
/*Start = 1 if the keyword from Start*/
/*
if(x == 5 ;)
*/				
char Data_Type (char Token_Num,char Start)	
{

	printf("i'm in Data_Type Func \n");
/********************* Check if valid Data type ****************/
	
	long int Type=0;
	
	//printf("init Type = %s\n", token);
	
	
	CheckAgain:
	printf("Valid-->Token_Num = %d   token = %s\n",Token_Num,token);

	switch (Token_Num)
	{
		case SIGNED:
			{
				//printf("i'm in Case SIGNED \n");
				Token_Num=Get_Tocken();				
				Type = Type+'S';				
				goto CheckAgain;
			}
			break;
			
		case LONG:
			{
				//printf("i'm in Case LONG \n");
				Token_Num=Get_Tocken();			
				Type = Type+'L';
				goto CheckAgain;
			}
			break;
			
		case SHORT:
			{
				//printf("i'm in Case SHORT \n");
				Token_Num=Get_Tocken();				
				Type = Type+'H';
				goto CheckAgain;
			}
			break;
			
		case UNSIGNED:
			{
				//printf("i'm in Case UNSIGNED \n");
				Token_Num=Get_Tocken();
				Type = Type+'U';
				goto CheckAgain;
			}
			break;
			
		case VOID:
			{
				//printf("i'm in Case VOID \n");
				Token_Num=Get_Tocken();
				Type = Type+'V';
				goto CheckAgain;
			}
			break;
			
		case CHAR:
			{
				//printf("i'm in Case CHAR \n");
				Token_Num=Get_Tocken();
				Type = Type+'C';
				goto CheckAgain;
			}
			break;
			
		case INT:
			{
				//printf("i'm in Case INT \n");
				Token_Num=Get_Tocken();
				Type = Type+'I';
				goto CheckAgain;
			}
			break;
		
		case FLOAT:
			{
				///printf("i'm in Case FLOAT \n");
				Token_Num=Get_Tocken();
				Type = Type+'F';
				goto CheckAgain;
			}
			break;
		
		case DOUBLE:
			{
				//printf("i'm in Case DOUBLE \n");
				Token_Num=Get_Tocken();
				Type = Type+'D';
				goto CheckAgain;
			}
			break;
			
		default: goto Is_Valid;
		break;
	}
	
	Is_Valid:
	
	printf("Valid-->Type of datatype = %d\n", Type);
	
	switch (Type)
	{	
		/*********** INT ********************/		
		case 310: //LLUI
			{
				//printf("LLUI valid DataType\n");
				strcpy(ReturnArray[0],"LLUI");
			}
			break;
			
		case 225: //LLI
			{
				//printf("LLI valid DataType\n");
				strcpy(ReturnArray[0],"LLI");
			}
			break;
			
		case 308: //LLSI
			{
				//printf("LLSI valid DataType\n");
				strcpy(ReturnArray[0],"LLSI");
			}
			break;
			
		case 232: //LSI
			{
				//printf("LSI valid DataType\n");
				strcpy(ReturnArray[0],"LSI");
			}
			break;
			
		case 149: //LI
			{
				//printf("LI valid DataType\n");
				strcpy(ReturnArray[0],"LI");
			}
			break;
			
		case 73: //I
			{
				//printf("I valid DataType\n");
				strcpy(ReturnArray[0],"I");
			
			}
			break;
			
		case 156: //SI
			{
				//printf("SI valid DataType\n");
				strcpy(ReturnArray[0],"SI");
			}
			break;	
		
		case 228: //HSI
			{
				//printf("HSI valid DataType\n");
				strcpy(ReturnArray[0],"HSI");
			}
			break;
			
		case 145: //HI
			{
				//printf("HI valid DataType\n");
				strcpy(ReturnArray[0],"HI");
			}
			break;
			
		case 230: //HUI
			{
				//printf("HUI valid DataType\n");
				strcpy(ReturnArray[0],"HUI");
			}
			break;
			
		/*********** CHAR ********************/	
		case 152: //UC
			{
				//printf("UC valid DataType\n");
				strcpy(ReturnArray[0],"UC");
			}
			break;
			
		case 150: //SC
			{
				//printf("SC valid DataType\n");
				strcpy(ReturnArray[0],"SC");
			}
			break;
			
		case 67: //C
			{
				//printf("C valid DataType\n");
				strcpy(ReturnArray[0],"C");
			}
			break;
		
		/*********** DOUBLE ********************/		
		case 144: //LD
			{
				//printf("LD valid DataType\n");
				strcpy(ReturnArray[0],"LD");
			}
			break;
			
		case 68: //D
			{
				//printf("D valid DataType\n");
				strcpy(ReturnArray[0],"D");
			}
			break;
		
		/*********** FLOAT ********************/		
		case 70: //F
			{
				//printf("F valid DataType\n");
				strcpy(ReturnArray[0],"F");
			}
			break;
		
		/*********** VOID ********************/		
		case 86: //V
			{
				//printf("V valid DataType\n");
				strcpy(ReturnArray[0],"V");
			}
			break;
			
		default:
			{
				printf("unvalid DataType\n");
				exit(1);
				return -1;
			}
			
	}
	
/********************* Goto handler functions ****************/
	{// second Token_Num 
	
	if (is_identifier(token) != IDIENTIFIER_NO)
	{
		//printf("secound Token_Num is valid identifier");
		strcpy(ReturnArray[1],token);
		
		Token_Num=Get_Tocken();
		//printf("secound Token_Num = %d\n", Token_Num);
	}
	else if ((strcmp(token,"(")) == 0) // variable handler (Pointer)
	{
		strcpy(ReturnArray[1],token);
		if(Start == 1){
			Pointer_Handler(ReturnArray);}
		return POINTER;
	}
	else if ((strcmp(token,"*")) == 0)// variable handler (Pointer)
	{
		printf("iam in valid data type\n");
		
		printf("%s\n",ReturnArray[0]);
		strcpy(ReturnArray[1],token);
		if(Start == 1){
		Pointer_Handler(ReturnArray);}
		return POINTER;
	}
	else if (((strcmp(token,",")) == 0 || (strcmp(token,")")) == 0) && Start == 0)// variable handler (Pointer)
	{
		strcpy(ReturnArray[1],token);
		if(Start == 1){
		Pointer_Handler(ReturnArray);}
		return DATA_TYPE_ONLY;
	}
	else 
	{
		//ERROR
		printf("error: must be * , ( , or identifier \n");
		return -1;
	}
}
	
	{// thired Token_Num 
	if ((strcmp(token,"[")) == 0) // variable handler (Array)
	{
		strcpy(ReturnArray[2],token);
		if(Start == 1)
		{
		Array_Handler(ReturnArray);}
		return ARRAY;
	}	
	else if ((strcmp(token,"(")) == 0) // Function handler
	{
		printf("thired Token_Num is bracket\n");
		strcpy(ReturnArray[2],token);
		if(Start == 1){
		Function_Handler(ReturnArray);}
		return FUNCTION;
	}
	else // variable handling function (variable)
	{
		strcpy(ReturnArray[2],token);
		if(Start == 1){
		Variable_Handler(ReturnArray);}
		return VARIABLE;
	}
	}
	
}

/*void Pointer_Handler(char 	arr[3][10])
{
	printf("i'm in Pointer handling function\n");
	printf("Array[0]= %s\n",arr[0]);
	printf("Array[1]= %s\n",arr[1]);
	printf("Array[2]= %s\n",arr[2]);
}*/
/*void Array_Handler(char 	arr[3][10])
{
	printf("i'm in Array handling function\n");
	printf("Array[0]= %s\n",arr[0]);
	printf("Array[1]= %s\n",arr[1]);
	printf("Array[2]= %s\n",arr[2]);
}/*
void Function_Handler(char 	arr[3][10])
{
	printf("i'm in Function handling function\n");
	printf("Array[0]= %s\n",arr[0]);
	printf("Array[1]= %s\n",arr[1]);
	printf("Array[2]= %s\n",arr[2]);
}*/

