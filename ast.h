
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
#define AST_READ 21
#define AST_ITEM_PRINT 22
#define AST_PRINT 23
#define AST_PRINT 23
#define AST_PRINT_STRING 24
#define AST_PRINT_EXPRESSION 25
#define AST_RETURN 26
#define AST_BLOCK 27
#define AST_COMMAND 28
#define AST_ATTRIBUATION 29
#define AST_ATTRIBUATION_VECTOR 30
#define AST_TYPE_CHAR 31
#define AST_TYPE_INT 32
#define AST_TYPE_FLOAT 33
#define AST_FUNCTION_DECLARATION 34
#define AST_FUNCTION_HEAD 35
#define AST_FUNCTION_PARAM 36

#include "hash.h"

typedef struct ast_node{
	int type;
	struct ast_node* son[MAX_SONS];
	HASH_ITEM* symbol;
}AST;

AST* astCreate(int type, HASH_ITEM* symbol,AST* son0, AST* son1, AST* son2, AST* son3);
void astPrint(AST* node, int level);
#endif