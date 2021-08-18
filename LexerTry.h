#ifndef _LEXER_FUNCTION_H
#define _LEXER_FUNCTION_H

//prototypes

int  Validate_Token(char str[]);
int DivideTokens(char ch);
int Get_Tocken();


#define IDIENTIFIER_YES 	127
#define IDIENTIFIER_NO	 	126
#define INT_NUM 	124
#define FLOAT_NUM	125

#endif