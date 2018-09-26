#include "ast.h"

AST* astCreate(int type,HASH_ITEM* symbol, AST* son0, AST* son1, AST* son2, AST* son3){
	AST* newNode;
	newNode = (AST*) calloc(1,sizeof(AST));
	newNode->type = type;
	newNode->symbol = symbol;
	newNode->son[0] = son0;
	newNode->son[1] = son1;
	newNode->son[2] = son2;
	newNode->son[3] = son3;

	return newNode;

}
void astPrint(AST* node,int level){
	int i;

	if(node == 0){
		return;
	}
	fprintf(stderr,"\n");
	
	for(i=0;i<level ;++i)
		fprintf(stderr, "  ");

	fprintf(stderr,"AST");
	fprintf(stderr,"\n");
	
	for(i=0;i<level ;++i)
		fprintf(stderr, "  ");
	fprintf(stderr,"(");
	
	fprintf(stderr,"\n");
	for(i=0;i<level+1;++i)
		fprintf(stderr, "  ");

	switch(node->type){
		case AST_SYMBOL: fprintf(stderr, "AST_SYMBOL" ); break;
		case AST_ADD: fprintf(stderr, "AST_ADD" ); break;
		case AST_MUL: fprintf(stderr, "AST_MUL" ); break;
		case AST_SUB: fprintf(stderr, "AST_SUB" ); break;
		case AST_DIV: fprintf(stderr, "AST_DIV" ); break;
		case AST_OPERATOR_LE: fprintf(stderr, "AST_OPERATOR_LE" ); break;
		case AST_OPERATOR_GE: fprintf(stderr, "AST_OPERATOR_GE" ); break;
		case AST_OPERATOR_EQ: fprintf(stderr, "AST_OPERATOR_EQ" ); break;
		case AST_OPERATOR_L: fprintf(stderr, "AST_OPERATOR_L" ); break;
		case AST_OPERATOR_G: fprintf(stderr, "AST_OPERATOR_G" ); break;
		case AST_OPERATOR_OR: fprintf(stderr, "AST_OPERATOR_OR" ); break;
		case AST_OPERATOR_AND: fprintf(stderr, "AST_OPERATOR_AND" ); break;
		default: fprintf(stderr, "UNKNOWN" ); break;

	}
	if(node->symbol != 0){
		fprintf(stderr, " %s",node->symbol->value);
	}

	for(i=0; i<MAX_SONS; i++){
		astPrint(node->son[i], level + 1);
	}
	fprintf(stderr,"\n");
	
	for(i=0;i<level ;++i)
		fprintf(stderr, "  ");

	fprintf(stderr,")\n");
}