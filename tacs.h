#ifndef TACS_HEADER
#define TACS_HEADER
#include "hash.h"
#include "ast.h"


#define TAC_UNKNOWN -1
#define TAC_SYMBOL 1
#define TAC_ADD 2
#define TAC_SUB 3
#define TAC_MULT 4
#define TAC_DIV 5
#define TAC_OR 6
#define TAC_AND 7
#define TAC_NOT 8
#define TAC_PRINT 9
#define TAC_READ 10
#define TAC_IF 11
#define TAC_GE 12
#define TAC_G 13
#define TAC_LE 14
#define TAC_L 15
#define TAC_EQ 16
#define TAC_MOV 17
#define TAC_LABLE 18
#define TAC_BEGINFUN 19
#define TAC_ENDFUN 20
#define TAC_IFZ 21
#define TAC_JUMP 22
#define TAC_CALL 23
#define TAC_ARG 24
#define TAC_RET 25
#define TAC_ATRI 28
#define TAC_ATRI_VEC 29
#define TAC_VAR_DECL 30
#define TAC_FUNC_HEAD 31
#define TAC_FUNCTION_PARAM 32
#define TAC_VAR_VEC_DECL 33
#define TAC_VECTOR_INIT 34
#define TAC_VEC_READ 35
#define TAC_TYPE_CHAR 36
#define TAC_TYPE_INT 37
#define TAC_TYPE_FLOAT 38
#define TAC_IDENTIFIER 39

typedef struct tac_struct{
    int type;
    HASH_ITEM* res;
    HASH_ITEM* op1;
    HASH_ITEM* op2;
    struct tac_struct *prev;
    struct tac_struct *next;
} TAC;

TAC* tacCreate(int type, HASH_ITEM* res, HASH_ITEM* op1, HASH_ITEM* op2);
void tacPrintSingle(TAC *tac);
void tacPrintBackwards(TAC *tac);

TAC* tacGenerate(AST* node);
TAC* tacJoin(TAC* l1, TAC* l2);
HASH_ITEM* makeTemp2();
HASH_ITEM* createLabel();
#endif