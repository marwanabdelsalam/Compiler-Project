#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Seperators.h"
#include "Linked_List_handler.h"

extern Variable *Head;
extern FILE *fileptr;	
char string_sep[50];
int Scope_Number = 0; 
extern int line;

char Is_Separator(char *Token)
{
	int i;
	char sep[8] = {',', ';','(',')','[' ,']','{','}'};
	
	if (strlen(Token) > 1)
	{
		return -1;
	}
    else 
	{
		int i;
		for (i=0; i <= 8 ; i++)
		{
			if (sep[i]== Token[0])
			{
				printf ("input %c is Separator \n", Token [0]);
				if(i == 6){
					Scope_Number++;
					printf("New Scope = %d \n",Scope_Number);
				}
				else if(i == 7){
					clear_scoop(&Head);
										Scope_Number--;

					printf("End Scope = %d \n",Scope_Number);
					PrintNodes(&Head);
				}
				return i+32;
				//break;
			}
				
			else
			{
				//printf ("input %c is not Separator \n",Token [0] );
			}
				
		}
		char ch;
		int count = 0;
		memset(string_sep,'\0',strlen(string_sep));
		if(Token[0] == '\''){
			while((ch = fgetc(fileptr)) != EOF){
				if(ch == '\''){
					if(count == 0){
						printf("%d:  error: empty character constant",line);
						exit(1);
					}
					else if(count >1){
						printf("%d: warning: overflow in implicit constant conversion",line);
					}
					printf("Separator Handlers-->there is a ' ' %s \n",string_sep);
					return CHAR_QUOT;
				}
				else{
					string_sep[count++] = ch;
				}
			}
		}
		else if(Token[0] == '\"'){
			while((ch = fgetc(fileptr)) != EOF)
			{
					if(ch == '\"'){
						if(count == 0){
							printf("%d:  error: empty character constant",line);
							exit(1);
						}

						printf("Separator Handlers-->there is a string %s \n",string_sep);
						return STRING_2QOUT;
					}
					else if(ch == '\\'){
						string_sep[count++] = fgetc(fileptr);
					}
					else{
						string_sep[count++] = ch;
					}
				}
				printf("%d:  error: empty character constant",line);
				exit(1);
		}
		//printf ("input %c is not Separator \n",Token [0] );
		return -1;
	}
		
}
