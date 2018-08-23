%{
    #include <stdio.h>
    #include <stdlib.h>    
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
%token TK_IDENTIFIER 
%token LIT_INTEGER   
%token LIT_FLOAT     
%token LIT_CHAR      
%token LIT_STRING    
%token TOKEN_ERROR   

%%
    program: cmdList
            ;
    
    cmdList: cmd cmdList
            |
            ;

    cmd: KW_IF exp cmd
            | TK_IDENTIFIER '=' exp;
            ;
    
    exp: LIT_INTEGER
        | TK_IDENTIFIER
        | exp '+' exp
        | exp OPERATOR_EQ exp
        | exp '-' exp
        | exp '*' exp
        | TK_IDENTIFIER 'd' exp 'b'
        | 'd' exp 'b'
        ;


%%

int yyerror(char *a){
    fprintf(stderr, "Syntax Error LOL at line %d\n", getLineNumber());
    exit(3);
}