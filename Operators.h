#ifndef _OPERATORS_H_
#define _OPERATORS_H_

unsigned int Is_operator(char *Token ,FILE **fptr);
typedef enum Operators{
	PLUS = 40,
	MINUS ,
	ASTRICS  ,
	DIVIDE  ,
	GREATERTHAN  ,
	LESSTHAN   ,
	EQUAL  ,
	MODULUS  ,
	NOT,
	OR,
	AND,
	FLIP,			/* ~ */
	DOUBLEPOINT,	/* : */
	QUESTIONMARK,	/* ? */
	EQUALEQUAL,
	NOTEQUAL,
	LESSTHANOREQUAL,
	GREATERTHANOREQUAL,
	DIVIDEEQUAL,	/* /= */
	ASTRICSEQUAL,	/* *= */
	OREQUAL,
	ANDEQUAL,
	PLUSPLUS,
	PLUSEQUAL,		/*63*/
	MINUSMINUS,
	MINUSEQUAL		/*65*/
	
}Operators;

#endif