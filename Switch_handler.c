#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Linked_List_handler.h"
#include "ArrayHandler.h"
#include "Switch_handler.h"
#include "Operators.h"
#include "Seperators.h"
#include "LexerTry.h"
#include "KeyWord.h"
#define IDIENTIFIER_YES 	127
#define IDIENTIFIER_NO	 	126
#define INT_NUM 	124
#define FLOAT_NUM	125

int Char_Number ;
extern int Scope_Number;
extern int line;
extern char token[30];

extern Variable *Head;
static int init = 0;

void Switch_handler(void)
{
	printf("iam in Switch handler...........****\n");
	char loc_name[15]="";
	char Loc_DataType[15]="";
	char loc_gettocken2=0;
	char loc_datatype=0;
	char loc_vartype=0;
	char loc_init=0;
	char get_token=0;
	//get_token=Get_Tocken();
	if(Get_Tocken() == OPEN_ARCH) 
	{
		printf("Im here 1\n");
		//switch(
		get_token=Get_Tocken();
		if (get_token==IDIENTIFIER_YES)
		{
			strcpy(loc_name,token);/*copy name of identifier in loc variable*/
			//switch(x
			get_token=Get_Tocken();
			if (get_token==CLOSE_ARCH)
			{
				//switch(x)
				int result = search(&Head,loc_name,loc_datatype,&loc_vartype,&loc_init);
				if (result==1)
				{
					//okay continue its identified before
					//check its type if it's float --> error

						//okay continue it's int or char
						if (Get_Tocken()== OPEN_BRACKET )
						{
							//switch(x){
							if (Get_Tocken()== CASE)
							{
								CASE_AGAIN1:
								if (Get_Tocken()== INT_NUM)
								{
									//switch(x){case 5
									if (Get_Tocken()== DOUBLEPOINT)
									{
										//switch(x){case 5:
										//call tree function
										get_token=Get_Tocken();
										TreeDecesion(get_token);
										//get a new token if case again goto ...
										get_token=Get_Tocken();
										if (get_token==CASE)
										{
											goto CASE_AGAIN1;
										}
										else if (get_token== CLOSE_BRACKET)
										{
											//passed all tests :D  
											return;
										}
										else 
										{
											printf("syntax error in line %d\n",line); 	 
											exit(1);
										}
								
									}
									else 
									{
										//switch(x){case 5,,
										printf("syntax error in line %d\n",line); 	 
										exit(1);

									}
								}
								else
								{
									//switch(x){case ,,
									//didn't find integer number after case 
									printf("syntax error in line %d\n",line); 	 
									exit(1);

								}
					
							}
							else 
							{
								//didn't find case after switch
								printf("syntax error in line %d\n",line); 	 
								exit(1);

							}
						}
						else
						{
							//switch(x),,
							printf("syntax error in line %d\n",line); 	 
							exit(1);

						}
					
				}
				else 
				{
					//error it's not identified before
					printf("undeclared first used in line %d\n",line); 	 
					exit(1);

				}

				
			}
			else 
			{
				//switch(x,,
				printf("syntax error in line %d\n",line); 	 
				exit(1);

			}

		}
		else if (get_token==INT_NUM)
		{
			//switch(5
			get_token=Get_Tocken();
			if (get_token==CLOSE_ARCH)
			{
				//switch(5)
				int result = search(&Head,loc_name,loc_datatype,&loc_vartype,&loc_init);
				if (result==1)
				{
					//okay continue its identified before
					//check its type if it's float --> error
					if ( loc_vartype==INT_NUM)
					{
						//okay continue it's int or char
						if (Get_Tocken()== OPEN_BRACKET )
						{
							//switch(5){
							if (Get_Tocken()== CASE)
							{
								CASE_AGAIN2:
								if (Get_Tocken()== INT_NUM)
								{
									//switch(5){case 5
									if (Get_Tocken()== DOUBLEPOINT)
									{
										//switch(5){case 5:
										//call tree function
										get_token=Get_Tocken();
										TreeDecesion(get_token);
										//get a new token if case again goto ...
										get_token=Get_Tocken();
										if (get_token==CASE)
										{
											goto CASE_AGAIN2;
										}
										else if (get_token== CLOSE_BRACKET)
										{
											//passed all tests :D  
											return;
										}
										else 
										{
											printf("syntax error in line %d\n",line); 	 
											exit(1);
										}
								
									}
									else 
									{
										//switch(5){case 5,,
										printf("syntax error in line %d\n",line); 	 
										exit(1);

									}
								}
								else
								{
									//switch(5){case ,,
									//didn't find integer number after case 
									printf("syntax error in line %d\n",line); 	 
									exit(1);

								}
					
							}
							else 
							{
								//didn't find case after switch
								printf("syntax error in line %d\n",line); 	 
								exit(1);

							}
						}
						else
						{
							//switch(5),,
							printf("syntax error in line %d\n",line); 	 
							exit(1);

						}
					}
					else
					{
						//error it's not int nor char
						printf("syntax error in line %d\n",line); 	 
						exit(1);

					}
				}
				else 
				{
					//error it's not identified before
					printf("syntax error in line %d\n",line); 	 
					exit(1);

				}			
			}
			else 
			{
				//switch(5,,
				printf("syntax error in line %d\n",line); 	 
				exit(1);

			}


		}
		else 
		{
			//switch(,,
			printf("syntax error in line %d\n",line); 	 
			exit(1);
		}
	}
	else
	{
		//switch,,
		printf("syntax error in line %d\n",line); 	 
		exit(1);

	}



}