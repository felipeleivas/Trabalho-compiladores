%{
    #include <stdio.h>
    #include <stdlib.h> 
    #include "ast.h"   
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
%token OPERATOR_EQ   
%token OPERATOR_OR   
%token OPERATOR_AND  
%token OPERATOR_NOT  
%token<symbol> TK_IDENTIFIER 
%token<symbol> LIT_INTEGER   
%token<symbol> LIT_FLOAT     
%token<symbol> LIT_CHAR      
%token<symbol> LIT_STRING    
%token TOKEN_ERROR   




%type<ast> expression
%type<ast> literal

%left '<' '>'
%left '+' '-'
%left '*' '/'

%union { struct hashItem  *symbol; struct ast_node* ast;}
%%

program: element 
        ;

element: variablelDeclaration element
        | functionDeclaration element
        |
        ;

variablelDeclaration: type TK_IDENTIFIER '=' expression ';'              {astPrint($4, 0);}
                    | type TK_IDENTIFIER 'q' LIT_INTEGER 'p' ';'
                    | type TK_IDENTIFIER 'q' LIT_INTEGER 'p' ':' arrayInitialization ';'
                    ;

type: KW_CHAR
    | KW_INT
    | KW_FLOAT
    ;

expression: literal 
        | TK_IDENTIFIER                         { $$ = astCreate(AST_SYMBOL, $1,0,0,0,0);}
        | TK_IDENTIFIER 'q' expression 'p'
        | TK_IDENTIFIER 'd' parameters 'b'
        | expression '+' expression             { $$ = astCreate(AST_ADD, 0,$1,$3,0,0);}
        | expression '-' expression             { $$ = astCreate(AST_SUB, 0,$1,$3,0,0);}
        | expression '*' expression             { $$ = astCreate(AST_MUL, 0,$1,$3,0,0);}
        | expression '/' expression             { $$ = astCreate(AST_DIV, 0,$1,$3,0,0);}
        | expression OPERATOR_LE expression
        | expression OPERATOR_GE expression
        | expression '>' expression
        | expression '<' expression
        | expression OPERATOR_EQ expression
        | expression OPERATOR_OR expression
        | expression OPERATOR_AND expression
        | OPERATOR_NOT expression
        | 'd' expression 'b'
        ;

parameters: expression parametersAux
            |
            ;

parametersAux: ',' expression parametersAux
            |
            ;

literal: LIT_CHAR       { $$ = astCreate(AST_SYMBOL, $1,0,0,0,0);}
        | LIT_FLOAT     { $$ = astCreate(AST_SYMBOL, $1,0,0,0,0);}
        | LIT_INTEGER   { $$ = astCreate(AST_SYMBOL, $1,0,0,0,0);}
        ;

arrayInitialization: literal arrayInitialization
                    |
                    ;

functionDeclaration: head body
                    ;

head: type TK_IDENTIFIER 'd' parametersDeclaration 'b'
    ;

parametersDeclaration: type TK_IDENTIFIER parametersDeclarationAux
            |
            ;

parametersDeclarationAux: ',' type TK_IDENTIFIER parametersDeclarationAux
            |
            ;

body: block
    ;

block: '{' commandList '}'
    ;

commandList: command ';' commandList
            |
            ;

command: atribuation
        | read
        | print
        | fluxControl
        | return
        | block
        |
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
            ;

printItemsAux: ',' LIT_STRING printItemsAux
            | ',' expression printItemsAux
            |
            ;

return: KW_RETURN expression
        ;

fluxControl: KW_IF expression KW_THEN command KW_ELSE command
            | KW_IF expression KW_THEN command 
            | KW_WHILE expression command
            ;

%%

int yyerror(char *a){
    fprintf(stderr, "Syntax Error at line %d\n", getLineNumber());
    exit(3);
}