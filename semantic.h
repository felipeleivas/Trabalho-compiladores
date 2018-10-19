#ifndef SEMANTIC
#define SEMANTIC

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "ast.h"

void setDeclaration(AST* node);
void checkUndeclared();
int isRedeclared(AST* node);
void handleRedeclared(AST* node);
int findTypeByAstNode(AST* node);


#endif