#ifndef SEMANTIC
#define SEMANTIC

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "ast.h"

void setDeclaration(AST* node);
int isRedeclared(AST* node);
void handleRedeclared(AST* node);
int findTypeByAstNode(AST* node);
void checkExpressionDataType(AST* root);
void checkInnerDataType(AST* node);
void checkCommands(AST* root);
void checkBlock(AST* block);

#endif