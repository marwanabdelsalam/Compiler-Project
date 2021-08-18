#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "LexerTry.h"
#include "FOR_Handler.h"
#include "ValidDataType-final.h"
#include "Seperators.h"
#include "Identifier.h"
#include "TreeFunction.h"
#include "Operators.h"
#include "FOR_Handler.h"
#define IDIENTIFIER_YES 	127
#define IDIENTIFIER_NO	 	126
#define INT_NUM 			124
#define FLOAT_NUM			125

extern char token[30];
extern int Scope_Number;
extern int line;
extern char ReturnArray[3][10];
int open_arch_FOR = 0;
int semi_numbers = 0;
/*
must have 2 ; inside ( )
for()
Next
2 cases {    }
or just one line 
*/
void For_Handler(){
	printf("FOR Handler-->You Are IN FOR FUNCTION..........************\n\n");
	if(Scope_Number == 0){
		printf("%d: error: expected '=', ',', ';', 'asm' or '_attribute_' before '%s' token",line,token);
	}
	int res = Get_Tocken();
	if(res == OPEN_ARCH){
			Scope_Number++;
	}
	else{
		printf("%d: error: expected '(' before %s",line,token);
		exit(1);
	}
	FIRST_AGAIN:
	res = Get_Tocken();
	if(res >= 0 && res <= 14){
		printf("%d: error: There is no initialization in for C88");
		exit(1);
	}
	else if(res == IDIENTIFIER_YES){
		//Go to ID Handler
			Syntax_Handler(1);
	}
	else if(res == OPEN_ARCH){
		open_arch_FOR++;
		goto FIRST_AGAIN;
	}
	else if(res == CLOSE_ARCH){
		open_arch_FOR--;
		goto FIRST_AGAIN;
	}
	else if(res == SEMI_COMMA){
		;
	}
	else{
		printf("%d: error: expected expression before %s in For Implementation",line,token);
		exit(1);	
	}
	//Get second part must be a condition 
		printf("FOR Handler-->2nd part..........************\n");
	if(open_arch_FOR != 0){
			printf("%d: error: expected expression before ')' in For Implementation",line,token);;
		exit(1);	
	}
	res = Get_Tocken();
	if(res == IDIENTIFIER_YES){
		//Go to ID Handler		
		Syntax_Handler(1);
	}
	else if(res == INT_NUM || res == FLOAT_NUM){
		//Numbers
		Syntax_Number(1);
	}
	else if(res == ASTRICS ){
		Syntax_Pointer();
	}
	else if(res == SEMI_COMMA ){
		;
	}
	else{
		printf("%d: error: expected expression before %s in For Implementation",line,token);
		exit(1);	
	}
	
	//get third paramter
	printf("FOR Handler-->3nd part..........************\n");
	res = Get_Tocken();
	if(res == IDIENTIFIER_YES){
		//Go to ID Handler
		Syntax_Handler(0);
	}
	else if(res == INT_NUM || res == FLOAT_NUM){
		//Numbers
		Syntax_Number(0);
	}
	else if(res == ASTRICS ){
		Syntax_Pointer();
	}
	else if(res == CLOSE_ARCH ){
		printf("FOR_Handler-->For implimented well\n");
	}
	else{
		printf("%d: error: expected expression before %s in For Implementation",line,token);
		exit(1);	
	}
	Scope_Number--;
	res = Get_Tocken();
	if(res == SEMI_COMMA){
		return;
	}
	else if(res == OPEN_BRACKET){
		;
		}
	else{
		printf("%d: error: expected expression before %s in For Implementation",line,token);
		exit(1);}
	char flag = 1,Breacket_counter = 0;
	do{
		res = Get_Tocken();
		if(res == 25 || res == 27){
			res = Get_Tocken();
			if(res != SEMI_COMMA){
				printf("Error in Break\n");
				exit(1);
				}
			//BREAK OR CONTINUE CASES
		}
		else if(res == OPEN_BRACKET){
			Breacket_counter++;
		}
	
		else if(res == CLOSE_BRACKET){
			
			if(Breacket_counter == 0){
				flag = 0;
			}
			else{
				Breacket_counter--;
			}
		}
		else{
			TreeDecesion(res);
		}
	}
	while(flag);
}