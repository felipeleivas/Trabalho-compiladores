
#ifndef AST_HEADER 
#define AST_HEADER 

#define MAX_SONS 4
#define AST_LITERAL 1
#define AST_OPERATOR_SUB 2
#define AST_OPERATOR_DIV 3
#define AST_OPERATOR_MUL 4
#define AST_OPERATOR_ADD 5
#define AST_OPERATOR_LE 6
#define AST_OPERATOR_GE 7
#define AST_OPERATOR_EQ 8
#define AST_OPERATOR_L 9
#define AST_OPERATOR_G 10
#define AST_OPERATOR_OR 11
#define AST_OPERATOR_AND 12
#define AST_OPERATOR_NOT 13
#define AST_ARRAY 14
#define AST_FUNCTION 15
#define AST_PARAMETER 16
#define AST_IF 17
#define AST_THEN 18
#define AST_ELSE 19
#define AST_WHILE 20

#include "hash.h"

typedef struct ast_node{
	int type;
	struct ast_node* son[MAX_SONS];
	HASH_ITEM* symbol;
}AST;

AST* astCreate(int type, HASH_ITEM* symbol,AST* son0, AST* son1, AST* son2, AST* son3);
void astPrint(AST* node, int level);
#endif