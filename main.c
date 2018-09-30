#include "lex.yy.h"
#include "util.h"
#include "hash.h"
#include "y.tab.h"
#include "ast.h"

extern HASH_TABLE *hashTable;
extern AST *programNode;

int main( int argc, char **argv)
{
    ++argv, --argc;  /* skip over program name */
    if ( argc > 0 )
        yyin = fopen( argv[0], "r" );
    else
        yyin = stdin;
    
    initMe();

    yyparse();
    FILE *p = fopen(argv[1],"w");
	printPogramToFile(programNode,p);	
	fclose(p);
    exit(0);
}
