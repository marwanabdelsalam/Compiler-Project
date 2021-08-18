#ifndef Linked_List_handler_H
#define Linked_List_handler_H


#define PARAMTER_NO_MAX   	10
#define FUNCTION_NAME_MAX   15
typedef struct Variable{
	char dataType[8];
	char Name[30];
	char scope;
	char Def_Num;
	char INIT;
	char Arr_Size;
	char Var_Type;
	struct Variable* Next;
}Variable;
 enum ReturnType{
	NEW_FUN = 0,
	OLD_FUN_SAME_RETURN,
	OLD_FUN_DIFFERNCE_RETURN,
	OLD_FUN_DIFFERNCE_PARAMTERS,
	REDECLARED_FUN,
	OLD_ONE
};

typedef struct Function_dataType{
	char paramters_dataTypes[PARAMTER_NO_MAX][10];/*paramters datatypes*/
	int  Paramter_Count;
	char Name[FUNCTION_NAME_MAX];/*Function name*/
	int scope;/*Scope of declleration*/
	char Def_Num;/**/
	char implemented;/*indecate for implemented or just datatype*/
	char returnVal[10];/*return data type*/
	struct Function_dataType *Next;
}Function_dataType;

typedef enum search_error_state{
	REDECLARED,
	NEW_VAR,
	CONFILCT
}search_error_state;

/*functions prototypes*/
void push(Variable **head,Variable **ptr);
void pop(Variable **head);
void clear_scoop(Variable **head);
void PrintNodes(Variable **Head);
int search(Variable **head,char name[],char datatype[],char *variable_type,char *initialized);
search_error_state search_init(Variable **head,char *name,char *datatype,char init,char variable_type,char size/*only for arrays*/);void PrintNodes_fun(Function_dataType **Head);


void push_func(Function_dataType **Head,Function_dataType **NewNode);
void pop_fun(Function_dataType **head);
void clear_scoop_fun(Function_dataType **head);
void PrintNodes_fun(Function_dataType **Head);
int Function_Search_Name(Function_dataType **Head,char Name[]);
#endif