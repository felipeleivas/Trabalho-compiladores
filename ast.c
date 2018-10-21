#include "ast.h"
extern HASH_TABLE *hashTable;


AST* astCreate(int type, HASH_ITEM* symbol, AST* son0, AST* son1, AST* son2, AST* son3){
	AST* newNode;
	newNode = (AST*) calloc(1,sizeof(AST));
	newNode->type = type;
	newNode->symbol = symbol;
	newNode->son[0] = son0;
	newNode->son[1] = son1;
	newNode->son[2] = son2;
	newNode->son[3] = son3;
	if(symbol)
		switch(symbol->type){
			case LIT_STRING: newNode->dataType = DATATYPE_STRING; break;
			case LIT_FLOAT: newNode->dataType = DATATYPE_FLOAT; break;
			case LIT_CHAR:
			case LIT_INTEGER: newNode->dataType = DATATYPE_INT; break;
			case TK_IDENTIFIER: break;
			default: fprintf(stderr,"[ERROR] Unexpect type %d\n",type);
		}


	return newNode;
}

void printSpaces(int level) {
	int i;
	fprintf(stderr,"\n");
	for(i=0;i<level ;++i)
		fprintf(stderr, "  ");
}

void astPrint(AST* node,int level){
	int i;

	if(node == 0){
		return;
	}
	
	printSpaces(level);

	switch(node->type){
		case AST_LITERAL: fprintf(stderr, "AST_LITERAL \n " ); break;
		case AST_OPERATOR_ADD: fprintf(stderr, "AST_ADD \n " ); break;
		case AST_OPERATOR_MUL: fprintf(stderr, "AST_MUL \n " ); break;
		case AST_OPERATOR_SUB: fprintf(stderr, "AST_SUB \n " ); break;
		case AST_OPERATOR_DIV: fprintf(stderr, "AST_DIV \n " ); break;
		case AST_OPERATOR_LE: fprintf(stderr, "AST_OPERATOR_LE \n " ); break;
		case AST_OPERATOR_GE: fprintf(stderr, "AST_OPERATOR_GE \n " ); break;
		case AST_OPERATOR_EQ: fprintf(stderr, "AST_OPERATOR_EQ \n " ); break;
		case AST_OPERATOR_L: fprintf(stderr, "AST_OPERATOR_L \n " ); break;
		case AST_OPERATOR_G: fprintf(stderr, "AST_OPERATOR_G \n " ); break;
		case AST_OPERATOR_OR: fprintf(stderr, "AST_OPERATOR_OR \n " ); break;
		case AST_OPERATOR_AND: fprintf(stderr, "AST_OPERATOR_AND \n " ); break;
		case AST_OPERATOR_NOT: fprintf(stderr, "AST_OPERATOR_NOT \n " ); break;
		case AST_VECTOR: fprintf(stderr, "AST_VECTOR \n " ); break;
		case AST_FUNCTION: fprintf(stderr, "AST_FUNCTION \n " ); break;
		case AST_PARAMETER: fprintf(stderr, "AST_PARAMETER \n " ); break;
		case AST_IF: fprintf(stderr, "AST_IF \n " ); break;
		case AST_THEN: fprintf(stderr, "AST_THEN \n " ); break;
		case AST_ELSE: fprintf(stderr, "AST_ELSE \n " ); break;
		case AST_WHILE: fprintf(stderr, "AST_WHILE \n " ); break;
		case AST_READ: fprintf(stderr, "AST_READ \n " ); break;
		case AST_PRINT: fprintf(stderr, "AST_PRINT \n " ); break;
		case AST_PRINT_STRING: fprintf(stderr, "AST_PRINT_STRING \n " ); break;
		case AST_PRINT_EXPRESSION: fprintf(stderr, "AST_PRINT_EXPRESSION \n " ); break;
		case AST_BLOCK: fprintf(stderr, "AST_BLOCK \n " ); break;
		case AST_RETURN: fprintf(stderr, "AST_RETURN \n " ); break;
		case AST_COMMAND: fprintf(stderr, "AST_COMMAND \n " ); break;
		case AST_ATTRIBUATION: fprintf(stderr, "AST_ATTRIBUATION \n " ); break;
		case AST_ATTRIBUATION_VECTOR: fprintf(stderr, "AST_ATTRIBUATION_VECTOR \n " ); break;
		case AST_TYPE_CHAR: fprintf(stderr, "AST_TYPE_CHAR \n " ); break;
		case AST_TYPE_INT: fprintf(stderr, "AST_TYPE_INT \n " ); break;
		case AST_TYPE_FLOAT: fprintf(stderr, "AST_TYPE_FLOAT \n " ); break;
		case AST_FUNCTION_DECLARATION: fprintf(stderr, "AST_FUNCTION_DECLARATION \n " ); break;
		case AST_FUNCTION_HEAD: fprintf(stderr, "AST_FUNCTION_HEAD \n " ); break;
		case AST_FUNCTION_PARAM: fprintf(stderr, "AST_FUNCTION_PARAM \n " ); break;
		case AST_VARIABLE_DECLARATION: fprintf(stderr, "AST_VARIABLE_DECLARATION \n " ); break;
		case AST_VECTOR_INITIALIZATION: fprintf(stderr, "AST_VECTOR_INITIALIZATION \n " ); break;
		case AST_VARIABLE_DECLARATION_VECTOR: fprintf(stderr, "AST_VARIABLE_DECLARATION_VECTOR \n " ); break;
		case AST_ELEMENT: fprintf(stderr, "AST_ELEMENT \n " ); break;
		case AST_IDENTIFIER: fprintf(stderr, "AST_IDENTIFIER \n " ); break;
		default: fprintf(stderr, "UNKNOWN, %d", node->type ); break;

	}
	if(node->symbol != 0){
		fprintf(stderr, " -%s",node->symbol->value);
	}

	if(node->son[0]) {
		
		printSpaces(level);
		fprintf(stderr,"{");

		for(i=0; i<MAX_SONS; i++){
			astPrint(node->son[i], level + 1);
		}
		
		printSpaces(level);
		fprintf(stderr,"}");

		printSpaces(level);
	}
}

void printPogramToFile(AST* node, FILE* outputFile){
	int i;

	if(node == 0){
		return;
	}
	switch(node->type){
		case AST_IDENTIFIER:
		case AST_LITERAL: 
			writeStringOnFile(node->symbol->value, outputFile); 
			break;

		case AST_OPERATOR_ADD:
			printPogramToFile(node->son[0],outputFile);
			writeStringOnFile(" + ", outputFile); 
			printPogramToFile(node->son[1],outputFile);
			break;

		case AST_OPERATOR_MUL:
			printPogramToFile(node->son[0],outputFile);
			writeStringOnFile(" * ", outputFile); 
			printPogramToFile(node->son[1],outputFile);
			break;
		case AST_OPERATOR_SUB:
			printPogramToFile(node->son[0],outputFile);
			writeStringOnFile(" - ", outputFile); 
			printPogramToFile(node->son[1],outputFile);
			break;
		case AST_OPERATOR_DIV: 
			printPogramToFile(node->son[0],outputFile);
			writeStringOnFile(" / ", outputFile); 
			printPogramToFile(node->son[1],outputFile);
			break;
		case AST_OPERATOR_LE: 
			printPogramToFile(node->son[0],outputFile);
			writeStringOnFile(" <= ", outputFile); 
			printPogramToFile(node->son[1],outputFile);
			break;
		case AST_OPERATOR_GE: 
			printPogramToFile(node->son[0],outputFile);
			writeStringOnFile(" >= ", outputFile); 
			printPogramToFile(node->son[1],outputFile);
			break;
		case AST_OPERATOR_EQ: 
			printPogramToFile(node->son[0],outputFile);
			writeStringOnFile(" == ", outputFile); 
			printPogramToFile(node->son[1],outputFile);
			break;
		case AST_OPERATOR_L: 
			printPogramToFile(node->son[0],outputFile);
			writeStringOnFile(" < ", outputFile); 
			printPogramToFile(node->son[1],outputFile);
			break;
		case AST_OPERATOR_G: 
			printPogramToFile(node->son[0],outputFile);
			writeStringOnFile(" > ", outputFile); 
			printPogramToFile(node->son[1],outputFile);
			break;
		case AST_OPERATOR_OR: 
			printPogramToFile(node->son[0],outputFile);
			writeStringOnFile(" or ", outputFile); 
			printPogramToFile(node->son[1],outputFile);
			break;

		case AST_OPERATOR_AND: 
			printPogramToFile(node->son[0],outputFile);
			writeStringOnFile(" and ", outputFile); 
			printPogramToFile(node->son[1],outputFile);
			break;

		case AST_OPERATOR_NOT:
			writeStringOnFile(" not ", outputFile); 
			printPogramToFile(node->son[0],outputFile);
			break;

		case AST_VECTOR:
			writeStringOnFile(node->symbol->value, outputFile); 
			writeStringOnFile("q", outputFile); 
			printPogramToFile(node->son[0],outputFile);
			writeStringOnFile("p", outputFile); 
			break; 
		case AST_FUNCTION: 
			writeStringOnFile(node->symbol->value, outputFile); 
			writeStringOnFile("d", outputFile); 
			printPogramToFile(node->son[0],outputFile);
			writeStringOnFile("b", outputFile);
			break;

		case AST_PARAMETER: 
			printPogramToFile(node->son[0],outputFile);
			if(node->son[1] != 0){ 
				writeStringOnFile(", ", outputFile);
				printPogramToFile(node->son[1],outputFile);
			}
			break;
		case AST_IF: 
			writeStringOnFile("if ",outputFile);
			printPogramToFile(node->son[0],outputFile);			
			printPogramToFile(node->son[1],outputFile);			
			break;
		case AST_THEN:
			writeStringOnFile(" then ",outputFile);
			printPogramToFile(node->son[0],outputFile);
			printPogramToFile(node->son[1],outputFile);
			break;
		case AST_ELSE: 
			writeStringOnFile(" else ",outputFile);
			printPogramToFile(node->son[0],outputFile);
			break;

		case AST_WHILE: 
			writeStringOnFile("while ",outputFile);
			printPogramToFile(node->son[0],outputFile);
			writeStringOnFile(" ",outputFile);
			printPogramToFile(node->son[1],outputFile);

			break;
		case AST_READ: 
			writeStringOnFile("read ",outputFile);
			writeStringOnFile(node->symbol->value,outputFile);
			break;
		case AST_PRINT: 
			writeStringOnFile("print ", outputFile);
			printPogramToFile(node->son[0],outputFile);
			break;

		case AST_PRINT_STRING: 
			writeStringOnFile(node->symbol->value, outputFile);
			if(node->son[0] != 0){
				writeStringOnFile(", ", outputFile);
				printPogramToFile(node->son[0],outputFile);
				}
			break;

		case AST_PRINT_EXPRESSION:
			printPogramToFile(node->son[0],outputFile);
			if(node->son[1] != 0){
				writeStringOnFile(", ", outputFile);
				printPogramToFile(node->son[1],outputFile);
				
			}
			break;
		case AST_BLOCK: 
			writeStringOnFile("{\n", outputFile);
			printPogramToFile(node->son[0],outputFile);
			writeStringOnFile("}\n", outputFile);
			break;

		case AST_RETURN: 
			writeStringOnFile("return ",outputFile);
			printPogramToFile(node->son[0],outputFile);
			break;
			
		case AST_COMMAND: 
			printPogramToFile(node->son[0],outputFile);
			writeStringOnFile(";\n", outputFile);
			printPogramToFile(node->son[1],outputFile);

			break;
		case AST_ATTRIBUATION:
			writeStringOnFile(node->symbol->value, outputFile);
			writeStringOnFile(" = ", outputFile);
			printPogramToFile(node->son[0],outputFile);
		
			break;
		case AST_ATTRIBUATION_VECTOR: 
			writeStringOnFile(node->symbol->value, outputFile);
			writeStringOnFile(" q", outputFile);
			printPogramToFile(node->son[0],outputFile);
			writeStringOnFile("p = ", outputFile);
			printPogramToFile(node->son[1],outputFile);
			break;
		
		case AST_TYPE_CHAR: 
			writeStringOnFile(" char ", outputFile);
			break;
		case AST_TYPE_INT:
			writeStringOnFile(" int ", outputFile);
			break;
		case AST_TYPE_FLOAT: 
			writeStringOnFile(" float ", outputFile);
			break;
		
		case AST_FUNCTION_DECLARATION: 
			printPogramToFile(node->son[0],outputFile);
			printPogramToFile(node->son[1],outputFile);
			break;

		case AST_FUNCTION_HEAD: 
			printPogramToFile(node->son[0],outputFile);
			writeStringOnFile(node->symbol->value, outputFile );
			writeStringOnFile(" d ", outputFile);
			printPogramToFile(node->son[1],outputFile);
			writeStringOnFile(" b ", outputFile);
			
			break;
		case AST_FUNCTION_PARAM: 
			printPogramToFile(node->son[0],outputFile);
			writeStringOnFile(node->symbol->value, outputFile );
			if(node->son[1] != 0){
				writeStringOnFile(" , ", outputFile);
				printPogramToFile(node->son[1],outputFile);
			}
			break;
		case AST_VARIABLE_DECLARATION: 
			printPogramToFile(node->son[0],outputFile);
			writeStringOnFile(node->symbol->value, outputFile );
			writeStringOnFile(" = ", outputFile );
			printPogramToFile(node->son[1],outputFile);
			writeStringOnFile(" ;\n", outputFile );
			break;
		
		case AST_VECTOR_INITIALIZATION: 
			writeStringOnFile(" ", outputFile );
			printPogramToFile(node->son[0],outputFile);
			if(node->son[1] != 0)
				printPogramToFile(node->son[1],outputFile);
			break;
		
		case AST_VARIABLE_DECLARATION_VECTOR: 
			printPogramToFile(node->son[0],outputFile);
			writeStringOnFile(node->symbol->value, outputFile );
			writeStringOnFile(" q", outputFile );
			printPogramToFile(node->son[1],outputFile);
			writeStringOnFile("p ", outputFile );
			
			if(node->son[2] != 0){
				writeStringOnFile(" : ", outputFile );
				printPogramToFile(node->son[2],outputFile);

			}
			writeStringOnFile(" ;\n", outputFile );
			break;
		
		case AST_ELEMENT: 
			printPogramToFile(node->son[0],outputFile);
			printPogramToFile(node->son[1],outputFile);
			break;
		default: fprintf(stderr, "UNKNOWN, %d", node->type ); break;

	}
	

}

void checkUndeclared(){
	checkUndeclaredHash(hashTable);
}
void writeStringOnFile(char* string, FILE* file){
	fwrite(string, 1 , sizeof(char) * strlen(string) , file );
}