#include "tacs.h"
extern HASH_TABLE *hashTable;

TAC* makeIfThenElse(TAC* condition, TAC* ifBlock, TAC* elseBlock);
TAC* makeIfThen(TAC* condition, TAC* codeBlock);
TAC* makeWhile(TAC* code0, TAC* code1);
void print(char *a){
    fprintf(stderr, a);
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
        default: print("TAC_UNKOWN");
    }
    if(tac->res) fprintf(stderr,",%s",tac->res->value); else print(",0"); 
    if(tac->op1) fprintf(stderr,",%s",tac->op1->value); else print(",0"); 
    if(tac->op2) fprintf(stderr,",%s",tac->op2->value); else print(",0"); 
    print("\n");
}
void tacPrintBackwards(TAC *tac){
    if(tac){
        tacPrintSingle(tac);
        tacPrintBackwards(tac->prev);
    }
    else{
    }
}

void tacPrintForwards(TAC *tac){
    if(tac){
        tacPrintForwards(tac->prev);
        tacPrintSingle(tac);
    }
    else{
    }
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

TAC* tacGenerate(AST* node){
    if(!node) return 0;

    TAC* result[MAX_SONS];
    int i;
    for(i=0; i< MAX_SONS; i++) 
    {
        result[i] = tacGenerate(node->son[i]);
    }
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
            return tacJoin(
                        tacJoin(result[0],result[1]),
                            tacCreate(returnTacSymbolBasedOnAstSymbol(node->type),makeTemp2(),
                                result[0]?result[0]->res:0,
                                result[1]?result[1]->res:0));
        case AST_RETURN:
            return tacJoin(
                result[0],
                tacCreate(returnTacSymbolBasedOnAstSymbol(node->type),
                    result[0]?result[0]->res:0,
                    0,0)); 
            
        case AST_OPERATOR_NOT: 
                return tacJoin(result[0],
                                tacCreate(returnTacSymbolBasedOnAstSymbol(node->type),makeTemp2(),
                                    result[0]?result[0]->res:0,0));


        case AST_FUNCTION_DECLARATION:{
                TAC* beginf = tacCreate(TAC_BEGINFUN, node->son[0]->symbol, 0, 0);
                TAC* endf = tacCreate(TAC_ENDFUN, node->son[0]->symbol, 0, 0);

                return tacJoin(
                            tacJoin(
                                tacJoin(
                                    result[0],
                                    beginf),
                                result[1]),
                        endf);
        }
        case AST_FUNCTION_HEAD:
            return tacJoin(result[0], result[1]);
        case AST_FUNCTION_PARAM:
            return tacJoin(tacCreate(TAC_FUNCTION_PARAM, node->symbol, 0 ,0),result[1]);
        case AST_VARIABLE_DECLARATION:
        case AST_VARIABLE_DECLARATION_VECTOR:
            return tacJoin(tacJoin(
                tacCreate(returnTacSymbolBasedOnAstSymbol(node->type),node->symbol,result[1]?result[1]->res:0,0),
                result[0]),
             result[2]);
        case AST_VECTOR_INITIALIZATION:
            return tacJoin(result[1],tacCreate(TAC_VECTOR_INIT,result[0]?result[0]->res:0,0,0));
        case AST_ATTRIBUATION:
        case AST_ATTRIBUATION_VECTOR:
            return tacJoin(
                    tacJoin(result[0],result[1]),
                        tacCreate(
                            returnTacSymbolBasedOnAstSymbol(node->type),node->symbol,
                            result[0]?result[0]->res:0,result[1]?result[1]->res:0)
                        );   
        case AST_FUNCTION:
            return tacJoin(result[0], tacCreate(TAC_CALL,makeTemp2(),node->symbol,0));                 
        
        case AST_PARAMETER:
        case AST_PRINT_STRING:
        case AST_PRINT_EXPRESSION:
                return tacJoin(  
                            tacJoin(
                                result[0],
                                tacCreate(TAC_ARG,node->symbol,0,0)
                            ),
                            result[1]  
                        );
        case AST_PRINT:
            return tacJoin(result[0], tacCreate(returnTacSymbolBasedOnAstSymbol(node->type), 0,0,0));
        case AST_READ:
            return tacJoin(result[0], tacCreate(returnTacSymbolBasedOnAstSymbol(node->type), node->symbol,0,0));
        case AST_VECTOR:
            return tacJoin(result[0], tacCreate(TAC_VEC_READ,makeTemp2(),node->symbol,result[0]->res));
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
    sprintf(name,"feliPPPP%de",serial++);
    return pushItem(hashTable,name,name,LIT_INTEGER);     
}

HASH_ITEM* createLabel() {
    static int currentLabel = 0;
    char fname[100];
    sprintf(fname,"LabEllLLL%deEE",currentLabel++);	
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
