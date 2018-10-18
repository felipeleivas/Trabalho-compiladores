#include "semantic.h"

void setDeclaration(AST* root) {
	AST* node;
	AST* dec;

	for(node= root; node ; node = node->son[1]){
		dec = node->son[0];
		switch(dec->type){
			case AST_VARIABLE_DECLARATION:
				if(dec->symbol->type != TK_IDENTIFIER){
					fprintf(stderr, "Symbol %s redeclared ",dec->symbol->value);
				}
		}
	}

}

void checkUndeclared() {

}