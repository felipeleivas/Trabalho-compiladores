#include "ast.h"

AST* astCreate(int type, HASH_ITEM* symbol, AST* son0, AST* son1, AST* son2, AST* son3){
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
		case AST_LITERAL: fprintf(stderr, "AST_LITERAL" ); break;
		case AST_OPERATOR_ADD: fprintf(stderr, "AST_ADD" ); break;
		case AST_OPERATOR_MUL: fprintf(stderr, "AST_MUL" ); break;
		case AST_OPERATOR_SUB: fprintf(stderr, "AST_SUB" ); break;
		case AST_OPERATOR_DIV: fprintf(stderr, "AST_DIV" ); break;
		case AST_OPERATOR_LE: fprintf(stderr, "AST_OPERATOR_LE" ); break;
		case AST_OPERATOR_GE: fprintf(stderr, "AST_OPERATOR_GE" ); break;
		case AST_OPERATOR_EQ: fprintf(stderr, "AST_OPERATOR_EQ" ); break;
		case AST_OPERATOR_L: fprintf(stderr, "AST_OPERATOR_L" ); break;
		case AST_OPERATOR_G: fprintf(stderr, "AST_OPERATOR_G" ); break;
		case AST_OPERATOR_OR: fprintf(stderr, "AST_OPERATOR_OR" ); break;
		case AST_OPERATOR_AND: fprintf(stderr, "AST_OPERATOR_AND" ); break;
		case AST_OPERATOR_NOT: fprintf(stderr, "AST_OPERATOR_NOT" ); break;
		case AST_VECTOR: fprintf(stderr, "AST_VECTOR" ); break;
		case AST_FUNCTION: fprintf(stderr, "AST_FUNCTION" ); break;
		case AST_PARAMETER: fprintf(stderr, "AST_PARAMETER" ); break;
		case AST_IF: fprintf(stderr, "AST_IF" ); break;
		case AST_THEN: fprintf(stderr, "AST_THEN" ); break;
		case AST_ELSE: fprintf(stderr, "AST_ELSE" ); break;
		case AST_WHILE: fprintf(stderr, "AST_WHILE" ); break;
		case AST_READ: fprintf(stderr, "AST_READ" ); break;
		case AST_ITEM_PRINT: fprintf(stderr, "AST_ITEM_PRINT" ); break;
		case AST_PRINT: fprintf(stderr, "AST_PRINT" ); break;
		case AST_PRINT_STRING: fprintf(stderr, "AST_PRINT_STRING" ); break;
		case AST_PRINT_EXPRESSION: fprintf(stderr, "AST_PRINT_EXPRESSION" ); break;
		case AST_BLOCK: fprintf(stderr, "AST_BLOCK" ); break;
		case AST_RETURN: fprintf(stderr, "AST_RETURN" ); break;
		case AST_COMMAND: fprintf(stderr, "AST_COMMAND" ); break;
		case AST_ATTRIBUATION: fprintf(stderr, "AST_ATTRIBUATION" ); break;
		case AST_ATTRIBUATION_VECTOR: fprintf(stderr, "AST_ATTRIBUATION_VECTOR" ); break;
		case AST_TYPE_CHAR: fprintf(stderr, "AST_TYPE_CHAR" ); break;
		case AST_TYPE_INT: fprintf(stderr, "AST_TYPE_INT" ); break;
		case AST_TYPE_FLOAT: fprintf(stderr, "AST_TYPE_FLOAT" ); break;
		case AST_FUNCTION_DECLARATION: fprintf(stderr, "AST_FUNCTION_DECLARATION" ); break;
		case AST_FUNCTION_HEAD: fprintf(stderr, "AST_FUNCTION_HEAD" ); break;
		case AST_FUNCTION_PARAM: fprintf(stderr, "AST_FUNCTION_PARAM" ); break;
		case AST_VARIABLE_DECLARATION: fprintf(stderr, "AST_VARIABLE_DECLARATION" ); break;
		case AST_VECTOR_INITIALIZATION: fprintf(stderr, "AST_VECTOR_INITIALIZATION" ); break;
		case AST_VARIABLE_DECLARATION_VECTOR: fprintf(stderr, "AST_VARIABLE_DECLARATION_VECTOR" ); break;
		case AST_ELEMENT: fprintf(stderr, "AST_ELEMENT" ); break;
		default: fprintf(stderr, "UNKNOWN, %d", node->type ); break;

	}
	if(node->symbol != 0){
		fprintf(stderr, " %s",node->symbol->value);
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
		case AST_FUNCTION: fprintf(stderr, "AST_FUNCTION" ); break;
		case AST_PARAMETER: fprintf(stderr, "AST_PARAMETER" ); break;
		case AST_IF: fprintf(stderr, "AST_IF" ); break;
		case AST_THEN: fprintf(stderr, "AST_THEN" ); break;
		case AST_ELSE: fprintf(stderr, "AST_ELSE" ); break;
		case AST_WHILE: fprintf(stderr, "AST_WHILE" ); break;
		case AST_READ: fprintf(stderr, "AST_READ" ); break;
		case AST_ITEM_PRINT: fprintf(stderr, "AST_ITEM_PRINT" ); break;
		case AST_PRINT: fprintf(stderr, "AST_PRINT" ); break;
		case AST_PRINT_STRING: fprintf(stderr, "AST_PRINT_STRING" ); break;
		case AST_PRINT_EXPRESSION: fprintf(stderr, "AST_PRINT_EXPRESSION" ); break;
		case AST_BLOCK: 
			writeStringOnFile("{\n", outputFile);
			printPogramToFile(node->son[0],outputFile);
			writeStringOnFile("}\n", outputFile);

			break;
		case AST_RETURN: fprintf(stderr, "AST_RETURN" ); break;
		case AST_COMMAND: 
			printPogramToFile(node->son[0],outputFile);
			break;
		case AST_ATTRIBUATION: 
		fprintf(stderr, "AST_ATTRIBUATION" );
		break;
		case AST_ATTRIBUATION_VECTOR: fprintf(stderr, "AST_ATTRIBUATION_VECTOR" ); break;
		
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
			writeStringOnFile(" q ", outputFile );
			printPogramToFile(node->son[1],outputFile);
			writeStringOnFile(" p ", outputFile );
			
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

void writeStringOnFile(char* string, FILE* file){
	fwrite(string, 1 , sizeof(char) * strlen(string) , file );
}