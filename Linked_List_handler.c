#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//#include "VariableHandler.h"
#include "Linked_List_handler.h"

extern  int Scope_Number ;
extern  int Function_Line_No ;

int Variable_Line_No = 0;

extern char Search_DataType[10];

typedef enum VarTybe{
	VARIABLE = 0,
	ARRAY,
	POINTER,
	FUNCTION,
}VarTybe;


//add first "LIFO stack"
void push(Variable **Head,Variable **NewNode)
{
	Variable *TEMP = *Head;
	*Head = *NewNode;
	(*NewNode)->Next = TEMP;
}
/*function to pop element*/
void pop(Variable **head)
{
	if(*head != NULL)
	{	
		Variable *temp = *head;
		*head = (*head)-> Next;
		free(temp);
	}
	else;
}
/*function to clear entire scoop*/
void clear_scoop(Variable **head)
{
	/*to loop while variables scope are equal to global scope_number variable*/
	while(  (*head) != NULL )
	{
		if((*head)->scope == Scope_Number){
		/*clear scope elements*/
		pop(head);}
		else{
			break;
		}
	}
}
//function to search for variable, pointers and arrays being used inside scopes to check if it's predeclared or not.
int search(Variable **head,char name[],char datatype[],char *variable_type,char *initialized)
{
	char found=0;/*flag to be raised if variable found redeclared before*/
	printf("iam in search function....\n");
	if(*head == NULL){
	return 0;
	}
	Variable *temp = *head;
	while( temp != NULL)
	{
		if(strcmp(name,temp->Name) == 0)/*if name found*/
		{
			found = 1;
			//printf("%s",datatype);
			strcpy(Search_DataType,temp->dataType);/*return variable data type at datatype pointer*/
			*variable_type = temp->Var_Type;	/*return variable  type at variable_type pointer*/
			*initialized = temp->INIT;			/*return variable initialized or not at initialized pointer*/
			return found;
		}
		temp = temp->Next; /*point to Next element*/
	}
	return found;
}
/*function to search for variable to check if it's declared before*/

search_error_state search_init(Variable **head,char *name,char *datatype,char init,char variable_type,char size/*only for arrays*/)/*"variable_type" 0 for variable, 1 for array 2 for pointer 3 for function*/
{
	Variable *temp = *head;
	char found=0;/*flag to be raised if variable found redeclared before*/
	char type=0;/*flag to be raised if two variables have same name and datatype*/
	/*to loop while variables scope are equal to global scope_number variable*/
	if(*head == NULL){
		return NEW_VAR;
	}
	
	while( temp != NULL)
	{
	
		if(temp->scope == Scope_Number)
		{
			
		if(strcmp(name,temp->Name) == 0)/*if the same name then we need another check for variable only*/
		{	
			if(variable_type == 0)/*search for variable*/
			{	
			
				if(strcmp(datatype,temp->dataType) == 0)/*if the same datatype then we need another check if its global and its scope == 0*/
				{
					if(Scope_Number==0)/*if global and both are initialized so same data section "REDECLARED"*/
					{
						if(( init == 1) && (temp->INIT == 1))
						{
							found = 1;	/*set flag*/
							type = 1;	/*same data type*/
						}
						else;	/*else so different data section its different variable*/
					}
					else	/*if not global "scoop != 0" then its REDECLARED*/
					{
						
						found = 1;	/*set flag*/
					}
				}
				else
				{
					found = 1;/*found same name but in different data type*/
				}
			}
			else if(variable_type == 1)/*for arrays*/
			{
				if(strcmp(datatype,temp->dataType) == 0)/*if the same datatype*/
				{
					if(init==temp->INIT) /*if both init*/
						found=1; /*error "redefinition of array x"*/
					else
					{
						if(size ==temp->Arr_Size);/*if same size*/
						else
							found=1; /*error "redefinition of array x"*/
					}	
				}
				else
				{
					/*return redeclared so error should be "previous declaration of x was here:"*/
					found = 1;
					type=1;
				}
			}
			else if((variable_type == 2)||(variable_type == 3))/*for pointers and functions*/
			{
				found = 1; /*same name same scoop error "conflicting types for 'variable' "*/
			}
			else
				printf("error invalid variable");
		}
		else{
			printf("New Name %s    old   %s",name,temp->Name);
		}
		if(found==1)
			break;
		
		temp = temp->Next; /*point to Next element*/}
		else{
			break;
		}
	}
	size=0;
	//same variable found with same data type
	if((found==1)&&(type==1))
	{
		Variable_Line_No = temp->Def_Num;	/*return line number for error message generation*/
		return REDECLARED;
	}
	//same variable found with different data type
	else if((found==1)&&(type==0))
	{
		Variable_Line_No = temp->Def_Num;	/*return line number for error message generation*/
		return CONFILCT;
	}
	//variable not found
	else
		return NEW_VAR;
	
}

void PrintNodes(Variable **Head){
	Variable *TEMP = *Head;
	while(TEMP != NULL){
		printf("Var Name = %s  and Type = %s  Scope = %d initialization = %d\n",TEMP->Name,TEMP->dataType,TEMP->scope,TEMP->INIT);
		TEMP = TEMP->Next;
	}	
}

void PrintNodes_fun(Function_dataType **Head){
	Function_dataType *TEMP = *Head;
	int i;
	while(TEMP != NULL){
		printf("fun Name = %s  and Return Type = %s  Scope = %d initialization = %d\n",TEMP->Name,TEMP->returnVal,TEMP->scope,TEMP->implemented);
		for(i = 0; i < TEMP-> Paramter_Count ;i++){
			printf("dataType:%d %s\t",i,TEMP->paramters_dataTypes[i]);
		}
		printf("\n");
		TEMP = TEMP->Next;
	}	
}

void push_func(Function_dataType **Head,Function_dataType **NewNode)
{
	Function_dataType *TEMP = *Head;
	*Head = *NewNode;
	(*NewNode)->Next = TEMP;
}

/*function to pop element*/
void pop_fun(Function_dataType **head)
{
	Function_dataType *temp;
	if(*head != NULL)
	{	
		temp = *head;
		*head = (*head)-> Next;
		free(temp);
	}
	else;
}

/*function to clear entire scoop*/
void clear_scoop_fun(Function_dataType **head)
{
	/*to loop while variables scope are equal to global scope_number variable*/
	while((*head)->scope == Scope_Number)
	{
		/*clear scope elements*/
		pop_fun(head);
	}
}

char Function_Search(Function_dataType **Head,Function_dataType **NewNode){
	Function_dataType * temp = * Head ;
		printf("Func Search-->Function search begin**************\n");
		int imp = (*NewNode)->implemented;
	if(temp == NULL){
		return NEW_FUN;
	}
	while(temp != NULL){
		
		//same name check
		if(strcmp(temp->Name,((*NewNode)->Name)) == 0){
			//same return type 
			if(strcmp(temp->returnVal,((*NewNode)->returnVal)) != 0){
				printf("Func Search-->Return type\n");
				Function_Line_No = temp->Def_Num;
					return OLD_FUN_DIFFERNCE_RETURN;
			}
			//check the count of paramters
			else if(temp->Paramter_Count != (*NewNode)->Paramter_Count){
				printf("Func Search-->paramter conflict count\n");
				Function_Line_No = temp->Def_Num;
					return OLD_FUN_DIFFERNCE_PARAMTERS;
			}
			//check for paramter datatypes
			else if(temp->Paramter_Count == (*NewNode)->Paramter_Count){
				int i = 0;
				for(i = 0 ; i < temp->Paramter_Count; i++){
					if(strcmp(temp->paramters_dataTypes[i],((*NewNode)->paramters_dataTypes[i])) != 0){
						printf("Func Search-->paramter conflict type\n");
						Function_Line_No = temp->Def_Num;
							return OLD_FUN_DIFFERNCE_PARAMTERS;
					}
				}
			}
			//check for implementation
			if((temp->implemented == (*NewNode)->implemented) && (temp->implemented == 1)){
						printf("Func Search-->Double implementation type\n");
						Function_Line_No = temp->Def_Num;
							return REDECLARED_FUN;
			}
			if(imp  == 1 ){
				temp->implemented = 1;
			}
				return OLD_ONE;
		}
		temp = temp->Next;
	}
	//New name 
	return NEW_FUN;

}



int Function_Search_Name(Function_dataType **Head,char Name[]){
	printf("Func Search name-->Start...................\n");
	Function_dataType * temp = * Head ;
	if(temp == NULL){
		return -1;
	}
	while(temp != NULL){
	if(strcmp(temp->Name,Name) == 0){
			printf("Func Search name-->END FOUND. ....%d\n",temp->Paramter_Count);

		return temp->Paramter_Count;
	}
	temp = temp->Next;
	}
	return -1;
}