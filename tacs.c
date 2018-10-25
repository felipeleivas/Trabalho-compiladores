#include "tacs.h"


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
    print("TAC(\n");
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
        default: print("TAC_UNKOWN");
    }
    if(tac->res) fprintf(stderr,",%s",tac->res->value); else print(",0"); 
    if(tac->op1) fprintf(stderr,",%s",tac->op1->value); else print(",0"); 
    if(tac->op2) fprintf(stderr,",%s",tac->op2->value); else print(",0"); 
    print(")\n");
}
void tacPrintBackwards(TAC *tac){
    tacPrintSingle(tac);
    tacPrintBackwards(tac->prev);
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
            return tacCreate(TAC_SYMBOL, node->symbol, 0,0);
        case AST_OPERATOR_ADD: return tacJoin(tacJoin(result[0],result[1]),tacCreate(TAC_ADD,makeTemp(),result[0]?result[0]->res:0,result[1]?result[1]->res:0));
        
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
