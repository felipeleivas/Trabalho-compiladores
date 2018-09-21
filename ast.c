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

	fprintf(stderr,"AST(");

	switch(node->type){
		case AST_SYMBOL: fprintf(stderr, "AST_SYMBOL" ); break;
		case AST_ADD: fprintf(stderr, "AST_ADD" ); break;
		case AST_MUL: fprintf(stderr, "AST_MUL" ); break;
		case AST_SUB: fprintf(stderr, "AST_SUB" ); break;
		case AST_DIV: fprintf(stderr, "AST_DIV" ); break;
		default: fprintf(stderr, "UNKNOWN" ); break;

	}
	if(node->symbol != 0){
		printf("%s\n",node->symbol->value);
	}

	for(i=0; i<MAX_SONS; i++){
		astPrint(node->son[i], level + 1);
	}
	fprintf(stderr,")");
}