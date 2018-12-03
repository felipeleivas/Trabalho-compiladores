%{
    #include <stdio.h>
    #include <stdlib.h> 
    #include "ast.h"   
    #include "hash.h"   
    #include "semantic.h"   
    #include "util.h"   
    #include "tacs.h"   
    AST* programNode;
    extern int semanticOutput;
    extern HASH_TABLE *hashTable;

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
%type<ast> atribuation
%type<ast> fluxControl
%type<ast> command
%type<ast> commandList
%type<ast> block
%type<ast> read
%type<ast> return
%type<ast> print
%type<ast> printItems
%type<ast> functionDeclaration
%type<ast> arrayInitialization
%type<ast> variablelDeclaration
%type<ast> parametersDeclaration
%type<ast> head
%type<ast> body
%type<ast> type
%type<ast> element

%left '<' '>'
%left '+' '-'
%left '*' '/'
%left OPERATOR_AND OPERATOR_OR
%left OPERATOR_NOT
%left OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_L OPERATOR_G

%union { struct hashItem  *symbol; struct ast_node* ast;}
%%

program: element {
                    programNode = $1;
                    fprintf(stderr, "\n\nAST PRINT\n");
                    astPrint($1,0);
                    setDeclaration($1);
                    checkUndeclared ();
                    checkCommands($1);

                    TAC* t = tacReverse(tacGenerate($1));
                    fprintf(stderr, "\n\nTAC PRINT\n");
                    tacPrintForwards(t);
                    fprintf(stderr, "\n\nASSEMBLY GENERATION PRINT\n");
                    asmGen(t);
                    return (semanticOutput);
                    } 
    ;

element: variablelDeclaration element { $$ = astCreate(AST_ELEMENT, 0,$1,$2,0,0);      }
        | functionDeclaration element { $$ = astCreate(AST_ELEMENT, 0,$1,$2,0,0);      }
        | {$$=0;}
        ;

variablelDeclaration: type TK_IDENTIFIER '=' expression ';'                                 { $$ = astCreate(AST_VARIABLE_DECLARATION, $2,$1,$4,0,0);      }
                    | type TK_IDENTIFIER 'q' LIT_INTEGER 'p' ';'                            { $$ = astCreate(AST_VARIABLE_DECLARATION_VECTOR, $2,$1,astCreate(AST_LITERAL, $4,0,0,0,0),0,0);      }
                    | type TK_IDENTIFIER 'q' LIT_INTEGER 'p' ':' arrayInitialization ';'    { $$ = astCreate(AST_VARIABLE_DECLARATION_VECTOR, $2,$1,astCreate(AST_LITERAL, $4,0,0,0,0),$7,0);      }
                    ;

arrayInitialization: literal arrayInitialization { $$ = astCreate(AST_VECTOR_INITIALIZATION, 0,$1,$2,0,0); }
                    | literal { $$ = astCreate(AST_VECTOR_INITIALIZATION, 0,$1,0,0,0); }
                    ;


type: KW_CHAR   { $$ = astCreate(AST_TYPE_CHAR, 0,0,0,0,0);}
    | KW_INT    { $$ = astCreate(AST_TYPE_INT, 0,0,0,0,0);}
    | KW_FLOAT  { $$ = astCreate(AST_TYPE_FLOAT, 0,0,0,0,0);}
    ;

expression: literal 
        | TK_IDENTIFIER                         { $$ = astCreate(AST_IDENTIFIER, $1,0,0,0,0);      }
        | TK_IDENTIFIER 'q' expression 'p'      { $$ = astCreate(AST_VECTOR, $1,$3,0,0,0);       }
        | TK_IDENTIFIER 'd' parameters 'b'      { $$ = astCreate(AST_FUNCTION, $1,$3,0,0,0);    }
        | TK_IDENTIFIER 'd' 'b'                 { $$ = astCreate(AST_FUNCTION, $1,0,0,0,0);     }
        | expression '+' expression             { $$ = astCreate(AST_OPERATOR_ADD, 0,$1,$3,0,0);}
        | expression '-' expression             { $$ = astCreate(AST_OPERATOR_SUB, 0,$1,$3,0,0);}
        | expression '*' expression             { $$ = astCreate(AST_OPERATOR_MUL, 0,$1,$3,0,0);}
        | expression '/' expression             { $$ = astCreate(AST_OPERATOR_DIV, 0,$1,$3,0,0);}
        | expression OPERATOR_LE expression     { $$ = astCreate(AST_OPERATOR_LE, 0,$1,$3,0,0); }
        | expression OPERATOR_GE expression     { $$ = astCreate(AST_OPERATOR_GE, 0,$1,$3,0,0); }
        | expression '>' expression             { $$ = astCreate(AST_OPERATOR_G, 0,$1,$3,0,0);  }
        | expression '<' expression             { $$ = astCreate(AST_OPERATOR_L, 0,$1,$3,0,0);  }  
        | expression OPERATOR_EQ expression     { $$ = astCreate(AST_OPERATOR_EQ, 0,$1,$3,0,0); }
        | expression OPERATOR_OR expression     { $$ = astCreate(AST_OPERATOR_OR, 0,$1,$3,0,0); }
        | expression OPERATOR_AND expression    { $$ = astCreate(AST_OPERATOR_AND, 0,$1,$3,0,0);}
        | OPERATOR_NOT expression               { $$ = astCreate(AST_OPERATOR_NOT, 0,$2,0,0,0); }
        | 'd' expression 'b'                    { $$ = $2;}
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


functionDeclaration: head body {$$ = astCreate(AST_FUNCTION_DECLARATION, 0,$1,$2,0,0);}
                    ;

head: type TK_IDENTIFIER 'd' parametersDeclaration 'b' {$$ = astCreate(AST_FUNCTION_HEAD, $2,$1,$4,0,0);}
    | type TK_IDENTIFIER 'd' 'b' {$$ = astCreate(AST_FUNCTION_HEAD, $2,$1,0,0,0);}
    ;

parametersDeclaration: type TK_IDENTIFIER parametersDeclaration {$$ = astCreate(AST_FUNCTION_PARAM, $2,$1,$3,0,0);}
            | ',' type TK_IDENTIFIER parametersDeclaration {$$ = astCreate(AST_FUNCTION_PARAM, $3,$2,$4,0,0);}
            | ',' type TK_IDENTIFIER {$$ = astCreate(AST_FUNCTION_PARAM, $3,$2,0,0,0);} 
            | type TK_IDENTIFIER {$$ = astCreate(AST_FUNCTION_PARAM, $2,$1,0,0,0);}
            ;

body: block {$$ = $1;}
    ;

block: '{' commandList '}' {$$ = astCreate(AST_BLOCK, 0, $2,0,0,0);}
    | '{' '}'              {$$ = astCreate(AST_BLOCK, 0, 0,0,0,0);}
    ;

commandList: command ';' commandList {$$ = astCreate(AST_COMMAND, 0, $1,$3,0,0);}
            | command ';' {$$ = astCreate(AST_COMMAND, 0, $1,0,0,0);}
            | ';' commandList {$$ = astCreate(AST_COMMAND, 0, 0,$2,0,0);}
            | ';' {$$ = astCreate(AST_COMMAND, 0, 0,0,0,0);}
            ;

command: atribuation    {$$ = $1;}
        | read          {$$ = $1;}
        | print         {$$ = $1;}
        | fluxControl   {$$ = $1;}
        | return        {$$ = $1;}
        | block         {$$ = $1;}
        ;

atribuation: TK_IDENTIFIER '=' expression { $$ = astCreate(AST_ATTRIBUATION, $1,$3,0,0,0);}
            | TK_IDENTIFIER 'q' expression 'p' '=' expression { $$ = astCreate(AST_ATTRIBUATION_VECTOR, $1,$3,$6,0,0);}
            ;

read: KW_READ TK_IDENTIFIER { $$ = astCreate(AST_READ, $2,0,0,0,0);}
    ;

print: KW_PRINT printItems { $$ = astCreate(AST_PRINT, 0,$2,0,0,0);}
    ;

printItems: LIT_STRING ',' printItems {$$ = astCreate(AST_PRINT_STRING, $1, $3,0,0,0);}
           | expression ',' printItems {$$ = astCreate(AST_PRINT_EXPRESSION, 0, $1,$3,0,0);}
           | LIT_STRING {$$ = astCreate(AST_PRINT_STRING, $1, 0,0,0,0);}
           | expression {$$ = astCreate(AST_PRINT_EXPRESSION, 0,$1,0,0,0);}
           ;

return: KW_RETURN expression {$$ = astCreate(AST_RETURN, 0, $2,0,0,0);}
        ;

fluxControl: KW_IF expression KW_THEN command KW_ELSE command {$$ = astCreate(AST_IF, 0,$2,astCreate(AST_THEN, 0,$4,astCreate(AST_ELSE, 0,$6,0,0,0),0,0),0,0);}
            | KW_IF expression KW_THEN command                {$$ = astCreate(AST_IF, 0,$2,astCreate(AST_THEN, 0,$4,0,0,0),0,0);}
            | KW_WHILE expression command                     {$$ = astCreate(AST_WHILE, 0,$2,$3,0,0);}
            ;

%%

int yyerror(char *a){
    fprintf(stderr, "Syntax Error at line %d\n", getLineNumber());
    exit(3);
}