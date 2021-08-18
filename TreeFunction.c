#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ValidDataType-final.h"
#include "Syntax_Handler.h"
#include "FOR_Handler.h"
#include "Switch_handler.h"
//#include "IF_Handler.h"

extern char token[30];
extern int line;

void TreeDecesion(int num){
	switch(num){
case 0: 
case 1: 
case 2:
case 3:
case 4:
case 5:
case 6:
case 7:
case 8:
case 9:
case 10: 
case 11:
case 12:
case 13:
case 14:
Data_Type(num,1); break;
//DataType Handler
break; 

case 15:
case 16:
case 17:
//UserDefin DataType
break;
case 18:
For_Handler();
break;
case 19:
case 20:
//Loops
break; 

case 21:
//If_Handler();
break;
case 22:
printf("%d: error a else without prevouis  if\n");
exit(1);
break;
case 23:
Switch_handler(); break;
case 24:
printf("%d: error a label with out switch\n");
break; 
case 25:
printf("%d: error a break with out prevouis loop\n");
exit(1);
break; 
case 26:
break; 
case 27:
printf("%d: error a continue with out prevouis loop\n");
exit(1);
break; 
case 28:
break; 
case 29:
//Typedef
break; 
case 30:
break; 
case 31:
break; 
case 32:
break; 
case 33:
break; 
case 34:
break; 
case 35:
break; 
case 36:
break; 
case 37:
break; 
case 38:
break; 
case 39:
break; 
case 42:
	Syntax_Pointer();
break;
case 124:
case 125:
	Syntax_Number(1);
break;
case 127:
	Syntax_Handler(1);
break; 
}
}