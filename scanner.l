%{
	#include "tokens.h"
	int lineNumber = 1;
%}

%x COMMENT

%%
[0-9]+		{	printf("Número: %s\n", yytext);								}
[i|I][f|F] 	{	printf("Foi escrito: IF\n");	 							}
"\n"		{	++lineNumber;													}

.  			{	printf("Era pra ser algo daora mas não foi %s \n",yytext); 	}
"//".*
"/*"  {BEGIN(COMMENT);}
<COMMENT>"*/" 	{BEGIN(INITIAL);}
<COMMENT>"\n" 	{++lineNumber;printf("comentario qubra de linha\n" );}
<COMMENT>.		


%%

void initMe(){

}


int yywrap(){
	return 1;
}

