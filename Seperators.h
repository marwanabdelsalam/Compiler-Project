#ifndef _SEPERATORS_H_
#define _SEPERATORS_H_

char Is_Separator(char *Token);
#define STRING_2QOUT	 123
#define CHAR_QUOT 		 122
typedef enum Seperators{
	COMMA = 32,
	SEMI_COMMA ,
	OPEN_ARCH  ,/*(*/
	CLOSE_ARCH  ,/*)*/
	OPEN_ARR  ,/*[*/
	CLOSE_ARR   ,/*]*/
	OPEN_BRACKET  ,/*{*/
	CLOSE_BRACKET  = 39  ,/*}*/
}Seperators;
#endif