#include "lex.yy.h"
#include "util.h"
#include "tokens.h"
#include "hash.h"

extern HASH_TABLE *hashTable;

int main( int argc, char **argv)
    {
    ++argv, --argc;  /* skip over program name */
    if ( argc > 0 )
            yyin = fopen( argv[0], "r" );
    else
            yyin = stdin;
	initMe();

	printHashTable(hashTable);
	
	yyparser();
}
