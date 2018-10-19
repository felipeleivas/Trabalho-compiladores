#include "semantic.h"

void setDataTypeForNode(AST* node){

}
void handleMissMatchingOfType(AST* node){
	fprintf(stderr, "MISS MATCHIMG OF TYPE of token %s\n",node->symbol->value);
}


void setDeclaration(AST* root) {
	AST* node;
	AST* dec;

	for(node= root; node ; node = node->son[1]){
		dec = node->son[0];
		switch(dec->type){
			case AST_VARIABLE_DECLARATION:
				if(isRedeclared(dec)){
					handleRedeclared(dec);
				}				
				dec->symbol->type = SYMBOL_VARIABLE;
				dec->dataType = findTypeByAstNode(dec->son[0]);
				dec->symbol->dataType[0] = findTypeByAstNode(dec->son[0]);
				if(dec->son[1] && dec->dataType != dec->son[1]->dataType)
					handleMissMatchingOfType(dec);
				break;



			case AST_VARIABLE_DECLARATION_VECTOR:
				if(isRedeclared(dec)){
					handleRedeclared(dec);
				}
				dec->symbol->type = SYMBOL_VECTOR;
				dec->dataType = findTypeByAstNode(dec->son[0]);
				dec->symbol->dataType[0] = findTypeByAstNode(dec->son[0]);
				if(dec->son[2]){
					AST* arrayElement = dec->son[2];
					for (; arrayElement != NULL; arrayElement = arrayElement->son[0]){
						if(arrayElement->dataType != dec->dataType){
							handleMissMatchingOfType(dec);
						}
					}
				}
				break;
				
			case AST_FUNCTION_DECLARATION:{

				AST* functionHead = dec->son[0];
				AST* functionType = functionHead->son[0];
				if(isRedeclared(functionHead)){
					handleRedeclared(functionHead);
				}
				functionHead->symbol->type = SYMBOL_FUNC;
				
				dec->son[0]->dataType = findTypeByAstNode(functionType);
				dec->son[0]->symbol->dataType[0] = findTypeByAstNode(functionType);

				
				AST* params  = functionHead->son[1];
				int index = 0;
				for(; params != 0; params = params->son[1]){
					params->symbol->type=SYMBOL_FUNC_PARAM;
					params->dataType = findTypeByAstNode(params->son[0]);
					params->symbol->dataType[index] = findTypeByAstNode(params->son[0]);
					++index;
				}
			}
			case AST_PRINT_STRING:
				dec->dataType = DATATYPE_STRING;
				break;
		}
	}

}

int findTypeByAstNode(AST* node){
	switch(node->type){
		case AST_TYPE_CHAR: 
		case AST_TYPE_INT: return DATATYPE_INT; 
		case AST_TYPE_FLOAT: return DATATYPE_FLOAT;
		default: fprintf(stderr, "Type unknow of token %s\n",node->symbol->value);
	}
	return (4);
}

int checkIfIsValueFromType(AST* node, int type){
	return node->symbol->type == type;
}
int isRedeclared(AST* node){
	return node->symbol->type != TK_IDENTIFIER;
}

void handleRedeclared(AST* node){
	fprintf(stderr, "Symbol %s redeclared\n",node->symbol->value);

}

void checkUndeclared() {

}