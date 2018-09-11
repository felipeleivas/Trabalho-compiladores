%{
    #include <stdio.h>
    #include <stdlib.h> 
    #include "hash.h"   
%}


%token KW_CHAR       
%token KW_INT        
%token KW_FLOAT      
%token KW_IF         
%token KW_THEN       
%token KW_ELSE       
%token KW_WHILE      
%token KW_READ       
%token KW_RETURN     
%token KW_PRINT      
%token OPERATOR_LE   
%token OPERATOR_GE    
%token OPERATOR_L   
%token OPERATOR_G  
%token OPERATOR_EQ   
%token OPERATOR_OR   
%token OPERATOR_AND  
%token OPERATOR_NOT  
%token TK_IDENTIFIER 
%token LIT_INTEGER   
%token LIT_FLOAT     
%token LIT_CHAR      
%token LIT_STRING    
%token TOKEN_ERROR   

%left '<' '>'
%left '+' '-'
%left '*' '/'

%union { struct hashItem  *symbol; }
%%

program: element 
        ;

element: variablelDeclaration element
        | functionDeclaration element
        | %empty
        ;

variablelDeclaration: type TK_IDENTIFIER '=' expression ';'  
                    | type TK_IDENTIFIER 'q' LIT_INTEGER 'p' ';'
                    | type TK_IDENTIFIER 'q' LIT_INTEGER 'p' ':' arrayInitialization ';'
                    ;

type: KW_CHAR
    | KW_INT
    | KW_FLOAT
    ;

expression: literal
        | TK_IDENTIFIER 
        | TK_IDENTIFIER 'q' expression 'p'
        | TK_IDENTIFIER 'd' parameters 'b'
        | expression '+' expression
        | expression '-' expression
        | expression '*' expression 
        | expression '/' expression 
        | expression OPERATOR_LE expression
        | expression OPERATOR_GE expression
        | expression OPERATOR_L expression
        | expression OPERATOR_G expression
        | expression OPERATOR_EQ expression
        | expression OPERATOR_OR expression
        | expression OPERATOR_AND expression
        | OPERATOR_NOT expression
        | 'd' expression 'b'
        ;

parameters: literal parametersAux
            | TK_IDENTIFIER parametersAux
            | %empty
            ;

parametersAux: ',' literal parametersAux
            | ',' TK_IDENTIFIER parametersAux
            | %empty
            ;

literal: LIT_CHAR
        | LIT_FLOAT
        | LIT_INTEGER
        ;

arrayInitialization: literal arrayInitialization
                    | %empty 
                    ;

functionDeclaration: head body
                    ;

head: type TK_IDENTIFIER 'd' parametersDeclaration 'b'
    ;

parametersDeclaration: type TK_IDENTIFIER parametersDeclarationAux
            | %empty
            ;

parametersDeclarationAux: ',' type TK_IDENTIFIER parametersDeclarationAux
            | %empty
            ;

body: block
    ;

block: '{' commandList '}'
    ;

commandList: command ';' commandList
            | %empty
            ;

command: atribuation
        | read
        | print
        | fluxControl
        | return
        | block
        | %empty
        ;

atribuation: TK_IDENTIFIER '=' expression
            | TK_IDENTIFIER 'q' expression 'p' '=' expression
            ;

read: KW_READ TK_IDENTIFIER
    ;

print: KW_PRINT printItems
    ;

printItems: LIT_STRING printItemsAux
            | expression printItemsAux
            | %empty
            ;

printItemsAux: ',' LIT_STRING printItemsAux
            | ',' expression printItemsAux
            | %empty
            ;

return: KW_RETURN expression
        ;

fluxControl: KW_IF expression KW_THEN fluxControlBody KW_ELSE fluxControlBody
            | KW_IF expression KW_THEN fluxControlBody 
            | KW_WHILE expression fluxControlBody
            ;

fluxControlBody: block
                | command
                ;

%%

int yyerror(char *a){
    fprintf(stderr, "Syntax Error at line %d\n", getLineNumber());
    exit(3);
}