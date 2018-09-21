
#ifndef AST_HEADER 
#define AST_HEADER 

#define MAX_SONS 4
#define AST_SYMBOL 1
#define AST_SUB 2
#define AST_DIV 3
#define AST_MUL 4
#define AST_ADD 5

#include "hash.h"

typedef struct ast_node{
	int type;
	struct ast_node* son[MAX_SONS];
	HASH_ITEM* symbol;
}AST;

AST* astCreate(int type, HASH_ITEM* symbol,AST* son0, AST* son1, AST* son2, AST* son3);
void astPrint(AST* node, int level);
#endif