#include "semantic.h"

extern HASH_TABLE *hashTable;

void setDataTypeForNode(AST* node){

}
void handleMissMatchingOfType(AST* node){
	while(node->symbol == NULL){
		node = node->son[0];
	}
		fprintf(stderr, "MISS MATCHIMG OF TYPE of token %s\n",node->symbol->value);
}


void setDeclaration(AST* root) {
	AST* node;
	AST* dec;
	AST* rightSide;
	AST* leftSide;

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
				if(dec->son[1] && dec->dataType != dec->son[1]->dataType){
					checkInnerDataType(node->son[1]);
					if(node->dataType != node->son[1]->dataType) 
						handleMissMatchingOfType(dec);
				}
					
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
					for (; arrayElement ; arrayElement = arrayElement->son[1]){
						if(arrayElement->son[0]->dataType != dec->dataType){
							handleMissMatchingOfType(dec);
						}
						arrayElement->dataType = dec->dataType;
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
				for(; params ; params = params->son[1]){
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

void checkExpressionDataType(AST* root){
	AST* node;
	AST* ope0;
	AST* ope1;

	for(node= root; node ; node = node->son[1]){
		ope0 = node->son[0];
		ope1 = node->son[1];
		switch(node->type){
			case AST_OPERATOR_ADD:
			case AST_OPERATOR_SUB:
			case AST_OPERATOR_DIV:
			case AST_OPERATOR_MUL:
				checkInnerDataType(ope0);
				checkInnerDataType(ope1);
				if(ope0->dataType == ope1->dataType && (ope0->dataType == DATATYPE_INT || ope0->dataType == DATATYPE_FLOAT) )
					node->dataType = ope0->dataType;
				else
					handleMissMatchingOfType(node);
				break;
			case AST_OPERATOR_AND:
			case AST_OPERATOR_OR:
				checkInnerDataType(ope0);
				checkInnerDataType(ope1);
				if(ope0->dataType == DATATYPE_BOOLEAN &&  ope0->dataType == ope1->dataType)
					node->dataType = DATATYPE_BOOLEAN;
				else
					handleMissMatchingOfType(node);
				break;
			case AST_OPERATOR_EQ:
			case AST_OPERATOR_G:
			case AST_OPERATOR_GE:
			case AST_OPERATOR_L:
			case AST_OPERATOR_LE:
				checkInnerDataType(ope0);
				checkInnerDataType(ope1);
				if(ope0->dataType == ope1->dataType && (ope0->dataType == DATATYPE_INT || ope0->dataType == DATATYPE_FLOAT) )
					node->dataType = DATATYPE_BOOLEAN;
				else
					handleMissMatchingOfType(node);
				break;
			case AST_OPERATOR_NOT:
				checkInnerDataType(ope0);
				if(ope0->dataType == DATATYPE_BOOLEAN)
					node->dataType = DATATYPE_BOOLEAN;
				else
					handleMissMatchingOfType(node);
		}
	}
}

void checkCommands(AST* root){
	AST*  node;
	for(node= root; node ; node = node->son[1]){
		if(node->son[0]->type == AST_FUNCTION_DECLARATION){
			AST* block = node->son[0]->son[1];
			checkBlock(block);
		}
	}
}

void checkBlock(AST* block){
	AST* rightSide;
	AST* command;
	for(command = block->son[0]; command; command = command->son[1]){
		AST* commandAction = command->son[0];
		switch(commandAction->type){
			case AST_ATTRIBUATION:
				rightSide = commandAction->son[0];
				checkInnerDataType(rightSide);
				if((commandAction->symbol->type == SYMBOL_FUNC_PARAM || commandAction->symbol->type == SYMBOL_VARIABLE) &&
							rightSide->dataType == commandAction->symbol->dataType[0])
						command->dataType = commandAction->dataType;
				else
					handleMissMatchingOfType(command);
				break;
			case AST_ATTRIBUATION_VECTOR:{
				AST* vectorIndex = commandAction->son[0];
				rightSide = commandAction->son[1];
				checkInnerDataType(vectorIndex);
				checkInnerDataType(rightSide);
				if(commandAction->symbol->type ==SYMBOL_VECTOR && vectorIndex->dataType == DATATYPE_INT &&
				 rightSide->dataType == commandAction->symbol->dataType[0]){
					 commandAction->dataType = rightSide->dataType;
				 }
				 else
				 	handleMissMatchingOfType(command);
				break;
			}
		}
	}
}

void checkInnerDataType(AST* node){
	checkExpressionDataType(node);
}