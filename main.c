#include "lex.yy.h"
#include "util.h"
#include "tokens.h"

int main( int argc, char **argv)
    {
    ++argv, --argc;  /* skip over program name */
    if ( argc > 0 )
            yyin = fopen( argv[0], "r" );
    else
            yyin = stdin;
        
    int line = getLineNumber();
	while(isRunning()){
    	int token = yylex();
    	if(line != getLineNumber()){
    		line = getLineNumber();
    		printf("\n");
    	}
    	if(token <= 255) printf("%c[%d] ",token,getLineNumber());
    	else{	
	    	switch (token){
	    		case KW_CHAR 		: printf("KW_CHAR[%d] ",getLineNumber());		break;
				case KW_INT 		: printf("KW_INT[%d] ",getLineNumber());		break;
				case KW_FLOAT 		: printf("KW_FLOAT[%d] ",getLineNumber());		break;
				case KW_IF 			: printf("KW_IF[%d] ",getLineNumber());			break;
				case KW_THEN 		: printf("KW_THEN[%d] ",getLineNumber());		break;
				case KW_ELSE 		: printf("KW_ELSE[%d] ",getLineNumber());		break;
				case KW_WHILE 		: printf("KW_WHILE[%d] ",getLineNumber());		break;
				case KW_READ 		: printf("KW_READ[%d] ",getLineNumber());		break;
				case KW_RETURN 		: printf("KW_RETURN[%d] ",getLineNumber());		break;
				case KW_PRINT 		: printf("KW_PRINT[%d] ",getLineNumber());		break;
				case OPERATOR_LE 	: printf("OPERATOR_LE[%d] ",getLineNumber());	break;
				case OPERATOR_GE 	: printf("OPERATOR_GE[%d] ",getLineNumber());	break;
				case OPERATOR_EQ 	: printf("OPERATOR_EQ[%d] ",getLineNumber());	break;
				case OPERATOR_OR 	: printf("OPERATOR_OR[%d] ",getLineNumber());	break;
				case OPERATOR_AND	: printf("OPERATOR_AND[%d] ",getLineNumber());	break;
				case OPERATOR_NOT 	: printf("OPERATOR_NOT[%d] ",getLineNumber());	break;
				case TK_IDENTIFIER 	: printf("TK_IDENTIFIER[%d] ",getLineNumber());	break;
				case LIT_INTEGER 	: printf("LIT_INTEGER[%d] ",getLineNumber());	break;
				case LIT_FLOAT 		: printf("LIT_FLOAT[%d] ",getLineNumber());		break;
				case LIT_CHAR 		: printf("LIT_CHAR[%d] ",getLineNumber());		break;
				case LIT_STRING 	: printf("LIT_STRING[%d] ",getLineNumber());	break;
				case TOKEN_ERROR 	: printf("TOKEN_ERROR[%d] ",getLineNumber());	break;
				default				: printf("VERY_ERROR[%d] ",getLineNumber());

	    	}
    	}
	}
}
