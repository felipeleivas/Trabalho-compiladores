#include "lex.yy.h"
#include "util.h"
#include "hash.h"
#include "y.tab.h"
#include "ast.h"

extern HASH_TABLE *hashTable;
extern AST *programNode;
extern int semanticOutput;
int main( int argc, char **argv)
{
    ++argv, --argc;  /* skip over program name */
    if ( argc > 0 )
        yyin = fopen( argv[0], "r" );
    else
        yyin = stdin;
    
    initMe();

    return yyparse();

    // fprintf(stderr,"\nThe program ended successfully\n");
    // FILE *p = fopen("output.txt","w");
	// printPogramToFile(programNode,p);	
	// fclose(p);
    // fprintf(stderr,"\nThe program print ended successfully\n");
    // printHashTable(hashTable);
    // return semanticOutput;
}
