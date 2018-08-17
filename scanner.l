%{
	#include "util.h"
	#include "tokens.h"
	int lineNumber = 1;
	int running = TRUE;
%}




%x COMMENT

%%
[0-9]+										{return LIT_INTEGER;}
"char" 										{return KW_CHAR;}
"int" 										{return KW_INT;}
"float" 									{return KW_FLOAT;}
"if"										{return KW_IF;}
"then"										{return KW_THEN;}
"else"										{return KW_ELSE;}
"while"										{return KW_WHILE;}
"read"										{return KW_READ;}
"return"									{return KW_RETURN;}
"print"										{return KW_PRINT;}
"<="										{return OPERATOR_LE;}
"=>"										{return OPERATOR_GE;}
"=="										{return OPERATOR_EQ;}
"not"										{return OPERATOR_NOT;}
"and"										{return OPERATOR_AND;}
"or"										{return OPERATOR_OR;}
[,|;|:|d|b|q|p|{|}|+|-|*|/|<|>|=|!|&|$|#] 	{return yytext[0];}
[_a-ce-or-z0-9]*[_a-ce-or-z]				{return TK_IDENTIFIER;}
"\n"										{++lineNumber;}
" "
"/*"  										{BEGIN(COMMENT);}
<COMMENT>"*/" 								{BEGIN(INITIAL);}
<COMMENT>"\n" 								{++lineNumber;}
<COMMENT>.		
.											{return TOKEN_ERROR;}

%%

void initMe(void){

}

int isRunning(void){
	return running;
}

int getLineNumber(void){
	return lineNumber;
}


int yywrap(void){
	running = FALSE;
	return 1;
}

