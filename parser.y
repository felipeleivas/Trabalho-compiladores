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
%type<ast> parameters
%type<ast> fluxControl
%type<ast> command

%left '<' '>'
%left '+' '-'
%left '*' '/'
%left OPERATOR_AND OPERATOR_OR
%left OPERATOR_NOT
%left OPERATOR_LE OPERATOR_GE OPERATOR_E

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
        | TK_IDENTIFIER                         { $$ = astCreate(AST_LITERAL, $1,0,0,0,0);}
        | TK_IDENTIFIER 'q' expression 'p'      { $$ = astCreate(AST_ARRAY, $1,$3,0,0,0);}
        | TK_IDENTIFIER 'd' parameters 'b'      { $$ = astCreate(AST_FUNCTION, $1,$3,0,0,0);}
        | TK_IDENTIFIER 'd' 'b'                 { $$ = astCreate(AST_FUNCTION, $1,0,0,0,0);}
        | expression '+' expression             { $$ = astCreate(AST_OPERATOR_ADD, 0,$1,$3,0,0);}
        | expression '-' expression             { $$ = astCreate(AST_OPERATOR_SUB, 0,$1,$3,0,0);}
        | expression '*' expression             { $$ = astCreate(AST_OPERATOR_MUL, 0,$1,$3,0,0);}
        | expression '/' expression             { $$ = astCreate(AST_OPERATOR_DIV, 0,$1,$3,0,0);}
        | expression OPERATOR_LE expression     { $$ = astCreate(AST_OPERATOR_LE, 0,$1,$3,0,0);}
        | expression OPERATOR_GE expression     { $$ = astCreate(AST_OPERATOR_GE, 0,$1,$3,0,0);}
        | expression '>' expression             { $$ = astCreate(AST_OPERATOR_L, 0,$1,$3,0,0);}
        | expression '<' expression             { $$ = astCreate(AST_OPERATOR_G, 0,$1,$3,0,0);}
        | expression OPERATOR_EQ expression     { $$ = astCreate(AST_OPERATOR_EQ, 0,$1,$3,0,0);}
        | expression OPERATOR_OR expression     { $$ = astCreate(AST_OPERATOR_OR, 0,$1,$3,0,0);}
        | expression OPERATOR_AND expression    { $$ = astCreate(AST_OPERATOR_AND, 0,$1,$3,0,0);}
        | OPERATOR_NOT expression               {$$ = astCreate(AST_OPERATOR_NOT, 0,$2,0,0,0);}
        | 'd' expression 'b'                    {$$ = $2;}
        ;

parameters: expression parameters            {$$ = astCreate(AST_PARAMETER, 0,$1,$2,0,0);}
            | ',' expression parameters      {$$ = astCreate(AST_PARAMETER, 0,$2,$3,0,0);}
            | ',' expression                 {$$ = astCreate(AST_PARAMETER, 0,$2,0,0,0);}
            | expression                     {$$ = astCreate(AST_PARAMETER, 0,$1,0,0,0);}
            ;

literal: LIT_CHAR       { $$ = astCreate(AST_LITERAL, $1,0,0,0,0);}
        | LIT_FLOAT     { $$ = astCreate(AST_LITERAL, $1,0,0,0,0);}
        | LIT_INTEGER   { $$ = astCreate(AST_LITERAL, $1,0,0,0,0);}
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
    | '{' '}'
    ;

commandList: command ';' commandList
            | command ';'
            | ';' commandList
            | ';'
            ;

command: atribuation    {$$ = 0;}
        | read          {$$ = 0;}
        | print         {$$ = 0;}
        | fluxControl   {astPrint($1, 0);}
        | return        {$$ = 0;}
        | block         {$$ = 0;}
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

fluxControl: KW_IF expression KW_THEN command KW_ELSE command {$$ = astCreate(AST_IF, 0,$2,astCreate(AST_THEN, 0,$4,0,0,0),astCreate(AST_ELSE, 0,$6,0,0,0),0);}
            | KW_IF expression KW_THEN command                {$$ = astCreate(AST_IF, 0,$2,astCreate(AST_THEN, 0,$4,0,0,0),0,0);}
            | KW_WHILE expression command                     {$$ = astCreate(AST_WHILE, 0,$2,$3,0,0);}
            ;

%%

int yyerror(char *a){
    fprintf(stderr, "Syntax Error at line %d\n", getLineNumber());
    exit(3);
}