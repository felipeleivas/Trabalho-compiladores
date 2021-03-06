%{
	#include "util.h"
	#include "hash.h"
	#include "ast.h"
	#include "y.tab.h"

	
	int lineNumber = 1;
	int running = TRUE;
	HASH_TABLE *hashTable;
	int getLineNumber(void){
		return lineNumber;
	}
%}

%x COMMENT

%%
[0-9]+										{yylval.symbol=pushItem(hashTable,yytext,yytext,LIT_INTEGER); return LIT_INTEGER;}
[0-9]+"."[0-9]+								{yylval.symbol=pushItem(hashTable,yytext,yytext,LIT_FLOAT); return LIT_FLOAT;}
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
">="										{return OPERATOR_GE;}
"=="										{return OPERATOR_EQ;}
"not"										{return OPERATOR_NOT;}
"and"										{return OPERATOR_AND;}
"or"										{return OPERATOR_OR;}
\"(\\.|[^"])*\"								{yylval.symbol=pushItem(hashTable,yytext,yytext,LIT_STRING);  return LIT_STRING;}
['][-a-zA-Z0-9][']                  	    {yylval.symbol=pushItem(hashTable,yytext,yytext,LIT_CHAR);  return LIT_CHAR;}
[-|,|;|:|d|b|q|p|{|}|+|*|/|<|>|=|!|&|$|#] 	{return yytext[0];}
[_ace-or-z0-9A-Z]*[_ace-or-zA-Z][_ace-or-z0-9A-Z]*	{yylval.symbol=pushItem(hashTable,yytext,yytext,TK_IDENTIFIER); return TK_IDENTIFIER;}
"\n"										{++lineNumber;}
[ \t]
"//".*


"/*"  										{BEGIN(COMMENT);}
<COMMENT>"*/" 								{BEGIN(INITIAL);}
<COMMENT>"\n" 								{++lineNumber;}
<COMMENT>.		
.											{return TOKEN_ERROR;}

%%

void initMe(void){
	hashTable = createHashTable(HASH_SIZE);
}

int isRunning(void){
	return running;
}

int yywrap(void){
	running = FALSE;
	return 1;
}
