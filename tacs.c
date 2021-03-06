#include "tacs.h"
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern HASH_TABLE *hashTable;

TAC* makeIfThenElse(TAC* condition, TAC* ifBlock, TAC* elseBlock);
TAC* makeIfThen(TAC* condition, TAC* codeBlock);
TAC* makeWhile(TAC* code0, TAC* code1);
void print(char *a){
    fprintf(stderr, a);
}

char * convertTypeToAssemblyType(int type){
    switch(type){
        case DATATYPE_INT: return "\"%d\"";
        case DATATYPE_FLOAT: return "%f";
        default: fprintf(stderr,"UNKOWN TYPE %d, %d\n",type,LIT_FLOAT);
    }
    return "%d",type;
}

TAC* createTempDeclaration(HASH_ITEM* item){

    return tacCreate(TAC_VAR_DECL, item,pushItem(hashTable,"0","0",LIT_INTEGER),0);
}
TAC* tacCreate(int type, HASH_ITEM* res, HASH_ITEM* op1, HASH_ITEM* op2){
    TAC* newTac = (TAC*) calloc(1,sizeof(TAC));
    newTac->type = type;
    newTac->res = res;
    newTac->op1 = op1;
    newTac->op2 = op2;
    newTac->prev = 0;
    newTac->next = 0;
    return newTac;
}
void tacPrintSingle(TAC *tac){
    if(!tac) return;
    switch(tac->type){
        case TAC_SYMBOL: print("TAC_SYMBOL");
            break;
        case TAC_ADD: print("TAC_ADD");
            break;
        case TAC_SUB: print("TAC_SUB");
            break;
        case TAC_DIV: print("TAC_DIV");
            break;
        case TAC_MULT: print("TAC_MULT");
            break;
        case TAC_AND: print("TAC_AND");
            break;
        case TAC_OR: print("TAC_OR");
            break;
        case TAC_NOT: print("TAC_NOT");
            break;
        case TAC_LE: print("TAC_LE");
            break;
        case TAC_GE: print("TAC_GE");
            break;
        case TAC_G: print("TAC_G");
            break;
        case TAC_EQ: print("TAC_EQ");
            break;
        case TAC_L: print("TAC_L");
            break;
        case TAC_LABLE: print("TAC_LABLE");
            break;
        case TAC_RET: print("TAC_RET");
            break;
        case TAC_ATRI: print("TAC_ATRI");
            break;
        case TAC_ARG: print("TAC_ARG");
            break;
        case TAC_BEGINFUN: print("TAC_BEGINFUN");
            break;
        case TAC_ENDFUN: print("TAC_ENDFUN");
            break;
        case TAC_MOV: print("TAC_MOV");
            break;
        case TAC_IFZ: print("TAC_IFZ");
            break;
        case TAC_JUMP: print("TAC_JUMP");
            break;
        case TAC_CALL: print("TAC_CALL");
            break;
        case TAC_ATRI_VEC: print("TAC_ATRI_VEC");
            break;
        case TAC_VAR_DECL: print("TAC_VAR_DECL");
            break;
        case TAC_FUNC_HEAD: print("TAC_FUNC_HEAD");
            break;
        case TAC_FUNCTION_PARAM: print("TAC_FUNCTION_PARAM");
            break;
        case TAC_PRINT: print("TAC_PRINT");
            break;
        case TAC_READ: print("TAC_READ");
            break;
        case TAC_VAR_VEC_DECL: print("TAC_VAR_VEC_DECL");
            break;
        case TAC_VECTOR_INIT: print("TAC_VECTOR_INIT");
            break;
        case TAC_VEC_READ: print("TAC_VEC_READ");
            break;
        case TAC_TYPE_CHAR: print("TAC_TYPE_CHAR");
            break;
        case TAC_TYPE_INT: print("TAC_TYPE_INT");
            break;
        case TAC_TYPE_FLOAT: print("TAC_TYPE_FLOAT");
            break;
        case TAC_IDENTIFIER: print("TAC_IDENTIFIER");
            break;
        case TAC_BEGIN_VEC_INI: print("TAC_BEGIN_VEC_INI");
            break;
        case TAC_END_VEC_INI: print("TAC_END_VEC_INI");
            break;
        case TAC_PARAMETER: print("TAC_PARAMETER");
            break;
        default: print("TAC_UNKOWN");
    }
    if(tac->res) fprintf(stderr,",%s",tac->res->key); else print(",0"); 
    if(tac->op1) fprintf(stderr,",%s",tac->op1->key); else print(",0"); 
    if(tac->op2) fprintf(stderr,",%s",tac->op2->key); else print(",0"); 
    print("\n");
}
void tacPrintBackwards(TAC *tac){
    if(tac){
        tacPrintSingle(tac);
        tacPrintBackwards(tac->prev);
    }
}

void tacPrintForwards(TAC *tac){
    if(tac){
        tacPrintSingle(tac);
        tacPrintForwards(tac->next);
    }
}

TAC* tacReverse(TAC* tac) {
    TAC* t = 0;
    for (t = tac; t->prev; t = t->prev ) {
        printf("t %d\n", t->type);
        t->prev->next = t;
    }
    return t;
}

int returnTacSymbolBasedOnAstSymbol(int astSymbol){
    switch(astSymbol){
        case AST_LITERAL: return TAC_SYMBOL; 
        case AST_OPERATOR_ADD: return TAC_ADD;
        case AST_OPERATOR_SUB: return TAC_SUB;
        case AST_OPERATOR_DIV: return TAC_DIV;
        case AST_OPERATOR_MUL: return TAC_MULT;
        case AST_OPERATOR_AND: return TAC_AND;
        case AST_OPERATOR_OR: return TAC_OR;
        case AST_OPERATOR_NOT: return TAC_NOT;
        case AST_OPERATOR_LE: return TAC_LE;
        case AST_OPERATOR_GE: return TAC_GE;
        case AST_OPERATOR_G: return TAC_G;
        case AST_OPERATOR_EQ: return TAC_EQ;
        case AST_OPERATOR_L: return TAC_L;
        case AST_FUNCTION_DECLARATION: return TAC_LABLE;
        case AST_ATTRIBUATION: return TAC_ATRI;
        case AST_RETURN: return TAC_RET;
        case AST_ATTRIBUATION_VECTOR: return TAC_ATRI_VEC;
        case AST_VARIABLE_DECLARATION: return TAC_VAR_DECL;
        case AST_VARIABLE_DECLARATION_VECTOR: return TAC_VAR_VEC_DECL;
        case AST_PRINT: return TAC_PRINT;
        case AST_READ: return TAC_READ;
        case AST_TYPE_CHAR: return TAC_TYPE_CHAR;
        case AST_TYPE_INT: return TAC_TYPE_INT;
        case AST_TYPE_FLOAT: return TAC_TYPE_FLOAT;
        default: return TAC_UNKNOWN;
        
    }
}

int parameterCounter = 0;
int calledFuncParameterCounter = 0;
char lastFuncName[90];
char lastCalledFunc[90];
TAC* tacGenerate(AST* node){
    if(!node) return 0;
    char buffer[50];
    TAC* result[MAX_SONS];
    int i;
    if(node->type == AST_FUNCTION_HEAD){
        strcpy(lastFuncName,node->symbol->value);
        parameterCounter = 0;
    }
    if(node->type == AST_FUNCTION){
        strcpy(lastCalledFunc,node->symbol->value);
        calledFuncParameterCounter = 0;
    }
    for(i=0; i< MAX_SONS; i++) 
    {
        result[i] = tacGenerate(node->son[i]);
    }
    HASH_ITEM *tempNode;
    switch(node->type){
        case AST_LITERAL: 
            return tacCreate(returnTacSymbolBasedOnAstSymbol(node->type), node->symbol, 0,0);
        case AST_OPERATOR_DIV: 
        case AST_OPERATOR_SUB: 
        case AST_OPERATOR_MUL: 
        case AST_OPERATOR_AND: 
        case AST_OPERATOR_OR: 
        case AST_OPERATOR_LE: 
        case AST_OPERATOR_GE: 
        case AST_OPERATOR_L: 
        case AST_OPERATOR_G: 
        case AST_OPERATOR_EQ: 
        case AST_OPERATOR_ADD: 
            tempNode = makeTemp2();
            
            return tacJoin(
                createTempDeclaration(tempNode),tacJoin(
                        tacJoin(result[0],result[1]),
                            tacCreate(returnTacSymbolBasedOnAstSymbol(node->type),tempNode,
                                result[0]?result[0]->res:0,
                                result[1]?result[1]->res:0)));
        case AST_RETURN:
            return tacJoin(
                result[0],
                tacCreate(returnTacSymbolBasedOnAstSymbol(node->type),
                    result[0]?result[0]->res:0,
                    0,0)); 
            
        case AST_OPERATOR_NOT: 
                tempNode = makeTemp2();
                return tacJoin(createTempDeclaration(tempNode),
                       tacJoin(result[0],
                            tacCreate(returnTacSymbolBasedOnAstSymbol(node->type),tempNode,
                                result[0]?result[0]->res:0,0)));
        


        case AST_FUNCTION_DECLARATION:{
            TAC* beginf = tacCreate(TAC_BEGINFUN, node->son[0]->symbol, 0, 0);
            TAC* endf = tacCreate(TAC_ENDFUN, node->son[0]->symbol, 0, 0);
            return tacJoin(
                        tacJoin(
                            tacJoin(
                                beginf,
                                result[0]),
                            result[1]),
                    endf);
        }
        case AST_FUNCTION_HEAD:
            return tacJoin(result[0], result[1]);
        case AST_FUNCTION_PARAM:
            sprintf(buffer,"%s%d",lastFuncName,parameterCounter++);
            return tacJoin(result[1],tacCreate(TAC_FUNCTION_PARAM, node->symbol, createItem(buffer,buffer,DATATYPE_INT) ,0));
        case AST_VARIABLE_DECLARATION:
        case AST_VARIABLE_DECLARATION_VECTOR:
            return tacJoin(tacJoin(
                tacCreate(returnTacSymbolBasedOnAstSymbol(node->type),node->symbol,result[1]?result[1]->res:0,0),
                result[0]),
             result[2]);
        case AST_VECTOR_INITIALIZATION:
            return tacJoin(tacCreate(TAC_VECTOR_INIT,result[0]?result[0]->res:0,0,0),result[1]);
        case AST_BEGIN_VEC_INITIALIZATION:{
            TAC* beginf = tacCreate(TAC_BEGIN_VEC_INI, node->son[0]->symbol, node->symbol, 0);
                TAC* endf = tacCreate(TAC_END_VEC_INI, node->son[0]->symbol, 0, 0);

                return tacJoin(
                            tacJoin(
                                beginf,
                                result[0]),
                        endf);
        }
        case AST_ATTRIBUATION:
        case AST_ATTRIBUATION_VECTOR:
            return tacJoin(
                    tacJoin(result[0],result[1]),
                        tacCreate(
                            returnTacSymbolBasedOnAstSymbol(node->type),node->symbol,
                            result[0]?result[0]->res:0,result[1]?result[1]->res:0)
                        );   
        case AST_FUNCTION:
            tempNode = makeTemp2();

            return tacJoin(
                    createTempDeclaration(tempNode),
                    tacJoin(result[0],tacCreate(TAC_CALL,tempNode,node->symbol,0))
                    
                );                 
        
        case AST_PARAMETER:
            sprintf(buffer,"%s%d",lastCalledFunc,calledFuncParameterCounter++);
                return tacJoin(tacCreate(TAC_ARG,result[0]?result[0]->res:0,createItem(buffer,buffer,DATATYPE_INT),0),result[1]);

        case AST_PRINT_STRING:
                return tacJoin(  
                            tacJoin(
                                result[0],
                                tacCreate(TAC_PRINT,node->symbol,0,0)
                            ),
                            result[1]  
                        );
        case AST_PRINT_EXPRESSION:
            return tacJoin(  
                            tacJoin(
                                result[0],
                                tacCreate(TAC_PRINT,result[0]->res,0,0)
                            ),
                            result[1]  
                        );
        case AST_PRINT:
            return result[0];
        case AST_READ:
            return tacJoin(result[0], tacCreate(returnTacSymbolBasedOnAstSymbol(node->type), node->symbol,0,0));
        case AST_VECTOR:
            tempNode = makeTemp2();
            return 
                tacJoin(createTempDeclaration(tempNode), 
                        tacJoin(result[0], 
                                tacCreate(TAC_VEC_READ,tempNode,node->symbol,result[0]->res)
                        )
                    );
        case AST_TYPE_CHAR:
        case AST_TYPE_FLOAT:
        case AST_TYPE_INT:
            return tacCreate(returnTacSymbolBasedOnAstSymbol(node->type),0,0,0);
        case AST_IF:
            if(node->son[1]->son[1]){
                return makeIfThenElse(result[0],result[1],tacGenerate(node->son[1]->son[1]));
            }
            return makeIfThen(result[0],result[1]);
        case AST_THEN:
            return result[0];
        case AST_WHILE:
            return makeWhile(result[0],result[1]);
        case AST_IDENTIFIER:
            return tacCreate(TAC_IDENTIFIER,node->symbol,0,0);
        default: return tacJoin(tacJoin(tacJoin(result[0],result[1]),result[2]),result[3]);
    }
    return 0;
}
TAC* tacJoin(TAC* l1, TAC* l2){
    TAC *aux;
    if(!l1) return l2;
    if(!l2) return l1;

    for(aux = l2; aux->prev; aux = aux->prev);

    aux->prev = l1;
    return l2;
}

HASH_ITEM* makeTemp2(){
    static int serial = 0;
    static char name[100];
    sprintf(name,"Variable%d",serial++);
    return pushItem(hashTable,name,name,LIT_INTEGER);     
}

HASH_ITEM* createLabel() {
    static int currentLabel = 0;
    char fname[100];
    sprintf(fname,"Label%d",currentLabel++);	
    return pushItem(hashTable,fname,fname, LIT_STRING);
}

TAC* makeIfThen(TAC* condition, TAC* codeBlock){
    HASH_ITEM *label = createLabel();
    TAC *ifTac = tacCreate(TAC_IFZ, label ,condition?condition->res:0,0);
    TAC* labelTac = tacCreate(TAC_LABLE, label, 0,0);
    return tacJoin(tacJoin(tacJoin(condition,ifTac), codeBlock),labelTac);
}
TAC* makeIfThenElse(TAC* condition, TAC* ifBlock, TAC* elseBlock){
    TAC *iftac, *jumptac, *labeltac, *labeltac2;
    HASH_ITEM *ifLabel, *elseLabel;
    ifLabel = createLabel();
	elseLabel = createLabel();
    iftac = tacCreate(TAC_IFZ, ifLabel,condition?condition->res:0,0);
	labeltac = tacCreate(TAC_LABLE, ifLabel, 0,0);
	jumptac = tacCreate(TAC_JUMP, elseLabel, 0, 0);
	labeltac2 = tacCreate(TAC_LABLE, elseLabel, 0,0);
    return tacJoin(tacJoin(tacJoin(tacJoin
    (tacJoin(tacJoin(condition,iftac),ifBlock),jumptac),labeltac),elseBlock),labeltac2);
}

TAC* makeWhile(TAC* testBlock, TAC* codeBlock) {
    TAC *testTac, *jumptac, *endLabelTac, *continueLabelTac;
    HASH_ITEM *endWhileLabel, *continueWhileLabel;
    endWhileLabel = createLabel();
	continueWhileLabel = createLabel();
    testTac = tacCreate(TAC_IFZ, endWhileLabel,testBlock?testBlock->res:0,0);
	endLabelTac = tacCreate(TAC_LABLE, endWhileLabel, 0,0);
	jumptac = tacCreate(TAC_JUMP, continueWhileLabel, 0, 0);
	continueLabelTac = tacCreate(TAC_LABLE, continueWhileLabel, 0,0);
    return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(continueLabelTac,testBlock),testTac),codeBlock),jumptac),endLabelTac);
}

void asmGen(TAC* first) {   
    FILE* fout = fopen("asm.s", "w");
    TAC *tac, *tacAux;
    int MAX_STRINGS = 99999;
	char *strings[MAX_STRINGS];
	int i, j=0;

	for(i = 0; i < MAX_STRINGS; i++)
		strings[i] = 0;

	i = 0;
    // int parameterCounter = 0;

fprintf(fout,"	.section	__TEXT,__text,regular,pure_instructions\n");
// fprintf(stderr, "Começou:\n");
    for(tac = first; tac; tac=tac->next) {
                    // fprintf(stderr, "tac->type = %d\n", tac->type);
        switch(tac->type) {
            case TAC_SYMBOL:
                break;
            case TAC_ADD:
                fprintf(fout, 
                    "##TAC_ADD\n"
                    "\tmovl	_%s(%%rip), %%eax\n"
                    "\taddl	_%s(%%rip), %%eax\n"
                    "\tmovl	%%eax, _%s(%%rip)\n",
                    tac->op1->key, tac->op2->key, tac->res->key);         
                break;
            case TAC_SUB: 
                fprintf(fout, 
                    "##TAC_SUB\n"
                    "\tmovl _%s(%%rip), %%esi\n"
                    "\tsubl _%s(%%rip), %%esi\n"
					"\tmovl %%esi, _%s(%%rip)\n"
                    , tac->op1->value, tac->op2->value, tac->res->value);
                break;
            case TAC_DIV:
                fprintf(fout, 
                    "##TAC_DIV\n"
					"\t.comm _%s,4,4\n"
                    "\tmovl _%s(%%rip), %%eax\n"
                    "\tcltd\n"
                    "\tidivl _%s(%%rip)\n"
					"\tmovl %%eax, _%s(%%rip)\n"
                    , tac->res->value, tac->op1->value, tac->op2->value, tac->res->value);
                break;
            case TAC_MULT: 
                fprintf(fout, 
                    "##TAC_MULT\n"
                    "\tmovl _%s(%%rip), %%eax\n"
                    "\timull _%s(%%rip), %%eax\n"
                    "\tmovl %%eax, _%s(%%rip)\n"
                    , tac->op1->value, tac->op2->value, tac->res->value);
                break;
            case TAC_AND:
                fprintf(fout, 
                    "##TAC_AND\n"
                    "\tmovl _%s(%%rip), %%eax\n"
                    "\timull _%s(%%rip), %%eax\n"
                    "\tcmp $1, %%eax\n"
                    "\tjne TrUE%d\n"
                    "\tmovl $1, _%s(%%rip)\n"
                    "\tjmp FAlSE%d\n"
                    "TrUE%d:\n\tmovl $0, _%s(%%rip)\n"
                    "FAlSE%d:\n "
                    , tac->op1->value, tac->op2->value, j,tac->res->value,j ,j , tac->res->value, j);
                j++;
                break;
            case TAC_OR: 
                    fprintf(fout, 
                    "##TAC_OR\n"
                    "\tmovl _%s(%%rip), %%eax\n"
                    "\taddl _%s(%%rip), %%eax\n"
                    "\tcmp $1, %%eax\n"
                    "\tjne TrUE%d\n"
                    "\tmovl $1, _%s(%%rip)\n"
                    "\tjmp FAlSE%d\n"
                    "TrUE%d:\n\tmovl $0, _%s(%%rip)\n"
                    "FAlSE%d:\n "
                    , tac->op1->value, tac->op2->value, j,tac->res->value,j ,j , tac->res->value, j);
                j++;
                break;
                break;
            case TAC_NOT:
                fprintf(fout,  
                    "\tmovl _%s(%%rip), %%eax\n"
                    "\tcmp $0, %%eax\n"
                    "\tjne TrUE%d\n"
                    "\tmovl $1, _%s(%%rip)\n"
                    "\tjmp FAlSE%d\n"
                    "TrUE%d:\n\tmovl $0, _%s(%%rip)\n"
                    "FAlSE%d:\n "
                    , tac->op1->value, j,tac->res->value,j ,j , tac->res->value, j);
                j++;
                break;
            case TAC_LE:            
                fprintf(fout, 
                    "##TAC_LE\n"
                    "\tmovl _%s(%%rip), %%eax\n"
                    "\tcmp %%eax, _%s(%%rip)\n"
                    "\tjl TrUE%d\n"
                    "\tmovl $1, _%s(%%rip)\n"
                    "\tjmp FAlSE%d\n"
                    "TrUE%d:\n\tmovl $0, _%s(%%rip)\n"
                    "FAlSE%d:\n "
                    , tac->op1->value, tac->op2->value, j, tac->res->value, j, j, tac->res->value, j);
                j++;
                break;
            case TAC_GE:            
                fprintf(fout, 
                    "##TAC_GE\n"
                    "\tmovl _%s(%%rip), %%eax\n"
                    "\tcmp %%eax, _%s(%%rip)\n"
                    "\tjg TrUE%d\n"
                    "\tmovl $1, _%s(%%rip)\n"
                    "\tjmp FAlSE%d\n"
                    "TrUE%d:\n\tmovl $0, _%s(%%rip)\n"
                    "FAlSE%d:\n "
                    , tac->op1->value, tac->op2->value, j, tac->res->value, j, j, tac->res->value, j);
                j++;
                break;
            case TAC_G:
                fprintf(fout, 
                    "##TAC_G\n"
                    "\tmovl _%s(%%rip), %%eax\n"
                    "\tcmp %%eax, _%s(%%rip)\n"
                    "\tjge TrUE%d\n"
                    "\tmovl $1, _%s(%%rip)\n"
                    "\tjmp FAlSE%d\n"
                    "TrUE%d:\n\tmovl $0, _%s(%%rip)\n"
                    "FAlSE%d:\n "
                    , tac->op1->value, tac->op2->value, j, tac->res->value, j, j, tac->res->value, j);
                j++;
                break;
            case TAC_EQ: 
                fprintf(fout, 
                    "##TAC_EQ\n"
                    "\tmovl _%s(%%rip), %%eax\n"
                    "\tcmp %%eax, _%s(%%rip)\n"
                    "\tjne TrUE%d\n"
                    "\tmovl $1, _%s(%%rip)\n"
                    "\tjmp FAlSE%d\n"
                    "TrUE%d:\n\tmovl $0, _%s(%%rip)\n"
                    "FAlSE%d:\n "
                    , tac->op1->value, tac->op2->value, j, tac->res->value, j, j, tac->res->value, j);
                j++;
                break;
            case TAC_L:
                 fprintf(fout, 
                    "##TAC_LT\n"
                    "\tmovl _%s(%%rip), %%eax\n"
                    "\tcmp %%eax, _%s(%%rip)\n"
                    "\tjle TrUE%d\n"
                    "\tmovl $1, _%s(%%rip)\n"
                    "\tjmp FAlSE%d\n"
                    "TrUE%d:\n\tmovl $0, _%s(%%rip)\n"
                    "FAlSE%d:\n "
                    , tac->op1->value, tac->op2->value, j, tac->res->value, j, j, tac->res->value, j);
                j++;
                break;
            case TAC_LABLE: 
                fprintf(fout, 
                    "## TAC_LABEL\n"
                    "%s:\n"
                    , tac->res->value);
                break;
            case TAC_RET: 
                    fprintf(fout,
                    "##TAC_RETURN\n"
                    "\tmovl	_%s(%%rip), %%eax\n",tac->res->value
                    );
                break;
            case TAC_ATRI: 
                fprintf(fout,
                    "#TAC_ATRI\n"
                    "movl _%s(%%rip), %%eax\n"
                    "movl %%eax, _%s(%%rip)\n",tac->op1->key, tac->res->key
                );
                break;
            case TAC_ARG: 
                break;
            case TAC_BEGINFUN:
                fprintf(fout, 
					"##TAC_BEGINFUN\n"
					"\t.globl _%s\n"
					"_%s:\n"
					"\t.cfi_startproc\n"
					"\tpushq	%%rbp\n"
					"\tmovq	%%rsp, %%rbp\n", tac->res->value, tac->res->value);
                break;
            case TAC_ENDFUN: 
                fprintf(fout, "##TAC_ENDFUN\n");
                fprintf(fout, "\tpopq	 %%rbp\n");
				fprintf(fout,
                    "\tretq \n"
					"\t.cfi_endproc\n");
                break;
            case TAC_MOV: 
                fprintf(fout,
                    "## TAC_MOV\n"
                    "\tmovl _%s(%%rip), %%eax \n"
                    "\tmovl %%eax, _%s(%%rip) \n" 
                    ,tac->op1->value,tac->res->value);
                break;
            case TAC_IFZ:
                fprintf(fout, 
                    "##TAC_IFZ\n"
                    "\tmovl _%s(%%rip), %%eax\n"                    
                    "\tcmp $0, %%eax\n"                    
                    "\tjz %s\n"
                    , tac->op1->value, tac->res->value);
                break;
            case TAC_JUMP: 
                fprintf(fout, 
                    "##TAC_JUMP\n"
                    "\tjmp %s", tac->res->value);
                break;  
            case TAC_CALL: fprintf(fout,
                        "\tcallq _%s\n"
                        "\tmovl %%eax, _%s(%%rip)\n", tac->op1->value,tac->res->value
                );
                break;
            case TAC_ATRI_VEC: print("TAC_ATRI_VEC");
                break;
            case TAC_VAR_DECL:
                break;  
            case TAC_FUNC_HEAD: print("TAC_FUNC_HEAD");
                break;
            case TAC_FUNCTION_PARAM:
                 fprintf(fout,
                    "##TAC_FUNCTION_PARAM\n"
                    "\tmovl _%s(%%rip), %%eax\n"
                    "\tmovl %%eax, _%s(%%rip)\n",tac->op1->value,tac->res->value
                    );
                    
                break;
            case TAC_PRINT:
                if(tac->res->type == LIT_STRING){
					fprintf(fout, 
							"##TAC_PRINT_STRING\n"
                            "\tleaq	.LC%d(%%rip), %%rdi\n"
                            "\tmovb	$0, %%al\n"
                            "\tcallq	_printf\n",i);
                        strings[i++]=tac->res->value;
				}
				else{
                    fprintf(fout, 
							"##TAC_PRINT_EXPRESSION\n"
                            "\tleaq	.LC%d(%%rip), %%rdi\n"
                            "\tmovl	_%s(%%rip), %%esi\n"
                            "\tmovb	$0, %%al\n"
                            "\tcallq	_printf\n",i,tac->res->value);
                            strings[i++]=convertTypeToAssemblyType(tac->res->dataType[0]);
				}
                break;
            case TAC_READ:
                fprintf(fout, 
                    "##TAC_READ\n"
                    "\tsubq	$16, %%rsp\n"
                    "\tmovq	_tempConvertStringToInt@GOTPCREL(%%rip), %%rdi\n"
                    "\tmovb	$0, %%al\n"
                    "\tcallq	_gets\n"
                    "\tmovq	_tempConvertStringToInt@GOTPCREL(%%rip), %%rdi\n"
                    "\tmovl	%%eax, -4(%%rbp)\n"
                    "\tmovb	$0, %%al\n"
                    "\tcallq	_atoi\n"
                    "\tmovl	%%eax, _%s(%%rip)\n"
                    "\txorl	%%esi, %%esi\n"
                    "\tmovl	%%eax, -8(%%rbp)\n"
                    "\tmovl	%%esi, %%eax\n"
                    "\taddq	$16, %%rsp\n",
                    tac->res->value);
                break;
            case TAC_VAR_VEC_DECL:
                break;
            case TAC_VECTOR_INIT:
                break;
            case TAC_VEC_READ:
                 fprintf(fout,
                    "## TAC_VEC_READ\n"
                    "\tmovl _%s+%d(%%rip), %%eax \n"
                    "\tmovl %%eax, _%s(%%rip) \n"	
                    ,tac->op1->value,4 * atoi(tac->op2->value),tac->res->value);
                break;
            case TAC_TYPE_CHAR: //print("TAC_TYPE_CHAR");
                break;
            case TAC_TYPE_INT: //print("TAC_TYPE_INT");
                break;
            case TAC_TYPE_FLOAT: //print("TAC_TYPE_FLOAT");
                break;
            case TAC_IDENTIFIER: //print("TAC_IDENTIFIER");
                break;
            case TAC_BEGIN_VEC_INI:
            case TAC_END_VEC_INI:
                break;
            default: print("TAC_UNKOWN");
        }

    }

    fprintf(fout, "\n\n	.section	__DATA,__data\n");
    for(tac = first; tac; tac=tac->next) {
                    // fprintf(stderr, "tac->type = %d\n", tac->type);
        switch(tac->type) {
            case TAC_VAR_DECL:
                fprintf(fout, 
					"##TAC_VAR_DECL\n"
					"\t.globl \t_%s\n"
					"\t.data\n"
					"_%s:\n"
					"\t.long \t%s\n", tac->res->value, tac->res->value, tac->op1->value);
            break;
            case TAC_VAR_VEC_DECL:
                fprintf(fout, 
					"##TAC_VAR_VEC_DECL\n"
					"\t.comm _%s,%d,4\n", tac->res->value, atoi(tac->op1->value));
            break;
            case TAC_BEGIN_VEC_INI:
                fprintf(fout,
                "##TAC_BEGIN_VEC_INIT\n"
                "_%s:\n",tac->op1->value
                ); 
                break;
            case TAC_VECTOR_INIT:
                fprintf(fout,
                    "\t.long %s\n",tac->res->value
                ); 
                break;
            case TAC_END_VEC_INI:
                fprintf(fout,
                "##TAC_END_VEC_INIT\n"
                );
                break;

                case TAC_FUNCTION_PARAM:
                fprintf(fout, 
                    "##TAC_FUNCTION_PARAM\n"
                    "\t.comm _%s,4,4\n"
                    "\t.comm _%s,4,4\n", tac->res->value ,tac->op1->value);
                break;
                
        }        
    }
    
    for(tac = first; tac; tac=tac->next) {
                    // fprintf(stderr, "tac->type = %d\n", tac->type);
        switch(tac->type) {
            case TAC_ARG:
                fprintf(fout, 
                    "##TAC_ARG\n"
                    "_%s:\n"
                    "\t.long %s\n", tac->op1->value ,tac->res->value);
                break;
                
        }        
    }

    HASH_ITEM *hashItem = NULL;
    for(i=0; i<hashTable->size; i++) {
        hashItem = hashTable->items[i];
        while(hashItem != NULL) {
            if(hashItem->value[0] <= '9' && hashItem->value[0] >= '0')
            fprintf(fout, 
					"##DECL_LITERAL\n"
					"\t.globl \t_%s\n"
					"\t.data\n"
					"_%s:\n"
					"\t.long \t%s\n", hashItem->value, hashItem->value, hashItem->value);
            hashItem = hashItem->next;
        }
    }
    fprintf(fout,
        ".zerofill __DATA,__common,_zero,4,2\n"
	"\t.comm	_tempConvertStringToInt,50,4\n"
    );
    for(i = 0; strings[i]; i++){
            fprintf(fout,      ".LC%d:\n"
                "\t.string %s\n"
                , i, strings[i]);
        }
}
