#ifndef _KEY_WORD_H_
#define _KEY_WORD_H_
unsigned int Is_Keyword(char *Token);
#define KEYWORD_COUNT	31
typedef enum Kewyword 
{
	   ERROR =	-1,
		
		LONG = 	0, 
	   SHORT = 	1,
	  SIGNED = 	2,
	UNSIGNED =  3,
	VOLATILE =  4,
	   CONST =	5,
	  STATIC = 	6,
	REGISTER =	7,
	    AUTO = 	8,
	  EXTERN = 	9,
	
		VOID =	10,
		CHAR = 	11,
		 INT = 	12,
	   FLOAT = 	13,
	  DOUBLE = 	14,
	
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
	   
} KEYWORD;
#endif