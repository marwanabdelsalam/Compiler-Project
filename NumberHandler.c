#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "NumberHandler.h"
double NumFloat = 0;
long long int Num = 0;

static char isFraction(char *str){
	int i;
	for(i = 0;i < strlen(str);i++){
		if(str[i] == '.'){
			return 1;
		}
	}
	return 0;
}
static char HexTransformation(char x){
	switch(x){
		case '0':return 'i';break;
		case '1':return 'f';break;
		case '2':return 2;break;
		case '3':return 3;break;
		case '4':return 4;break;
		case '5':return 5;break;
		case '6':return 6;break;
		case '7':return 7;break;
		case '8':return 8;break;
		case '9':return 9;break;
		case 'A':case 'a':return 10;break;
		case 'B':case 'b':return 11;break;
		case 'C':case 'c':return 12;break;
		case 'D':case 'd':return 13;break;
		case 'E':case 'e':return 14;break;
		case 'F':case 'f':return 15;break;
	}
}
/*
Function Input:
1-string of numbers to handle it
2-Void pointer that points to the op
3-Op type:	int = 0
			float = 1
*/

char GetNumber(char *str){
	int i = 0;
	Num = 0;
	if(strlen(str) == 1){
		if(str[0] == '.'){
			return -1;
		}
		else{
		 Num = atoi(str);
			  printf("decimal Number OP = %d\n",Num);
			  			return INT_NUM;	
		}
	}
	//Check for zero digit
	if(str[0] == '0'){
		//Binary representation 
		if(str[1] == 'b' || str[1] == 'B'){	
			strrev(str);
			while(str[i] != 'b' && str[i] != 'B'){
				if(str[i] > '1'){
					printf("error: invalid suffix \"%s\" on integer constant",strrev(str));
					exit(1);
				}
				Num += ((str[i]-'0')*pow(2,i));
				i++;
			}
			printf("Binary Number OP = %d\n",Num);
			return INT_NUM;
		}
		//Hex represenstion
		else if(str[1] == 'x' || str[1] == 'X'){
			strrev(str);
			while(str[i] != 'x' && str[i] != 'X'){
				if(isxdigit(str[i]) == 0){
					printf("error: invalid suffix \"%s\" on integer constant",strrev(str));
					exit(1);					
				}
				Num += HexTransformation(str[i])*pow(16,i);
				i++;
			}
			printf("Hexa Number OP = %d\n",Num);
			return INT_NUM;
		}
		//Octal
		else if(str[1] >= '0' && str[1] <= '8'){
			strrev(str);
			while(i < (strlen(str)-1) ){
				if(str[i] < '0' || str[i] > '8'){
					printf("error: invalid suffix \"%s\" on integer constant",strrev(str));
					exit(1);					
				}
				
				Num += ((str[i]-'0')*pow(8,i));
				i++;
			}
			printf("Octal Number OP = %d\n",Num);
						return INT_NUM;

		}
		else if(str[1] == '.'){
			//Fraction
			NumFloat =(float) atof(str);
			printf("Float Number OP = %f\n",(float)NumFloat);
						return FLOAT_NUM;

		}
	}
	else{
		//Check for Fraction
		if(isFraction(str)){
			NumFloat =(float) atof(str);
			printf("Float Number OP = %f\n",(float)NumFloat);
						return FLOAT_NUM;

		}
		else{
		//Decimal Number
			  Num = atoi(str);
			  printf("decimal Number OP = %d\n",Num);
			  			return INT_NUM;

		}
	}
	
}



