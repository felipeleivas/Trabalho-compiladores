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
				switch(dec->son[0]->type){
					case AST_TYPE_CHAR: 
					case AST_TYPE_INT: dec->dataType = DATATYPE_INT; break;
					case AST_TYPE_FLOAT: dec->dataType = DATATYPE_FLOAT; break;
					default: fprintf(stderr, "Type unknow of token %s\n",dec->symbol->value);
				}
				if(dec->son[1] && dec->dataType != dec->son[1]->dataType)
					handleMissMatchingOfType(dec);
				break;



			case AST_VARIABLE_DECLARATION_VECTOR:
				if(isRedeclared(dec)){
					handleRedeclared(dec);
				}
				dec->symbol->type = SYMBOL_VECTOR;
				switch(dec->son[0]->type){
					case AST_TYPE_CHAR: 
					case AST_TYPE_INT: dec->dataType = DATATYPE_INT; break;
					case AST_TYPE_FLOAT: dec->dataType = DATATYPE_FLOAT; break;
					default: fprintf(stderr, "Type unknow of token %s\n",dec->symbol->value);
				}
				if(dec->son[2]){
					AST* arrayElement = dec->son[2];
					for (; arrayElement != NULL; arrayElement = arrayElement->son[0]){
						// fprintf(stderr,"ERR %s %d %s %d\n",dec->symbol->value,dec->dataType,arrayElement->symbol->value,arrayElement->dataType);
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
				
				switch(functionType->type){
					case AST_TYPE_CHAR: 
					case AST_TYPE_INT: dec->son[0]->dataType = DATATYPE_INT; break;
					case AST_TYPE_FLOAT: dec->son[0]->dataType = DATATYPE_FLOAT; break;
					default: fprintf(stderr, "Type unknow of token %s\n",dec->symbol->value);

				}
				break;
			}

		}
	}

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