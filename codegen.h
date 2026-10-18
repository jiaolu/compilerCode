#ifndef CODEGEN_H
#define CODEGEN_H
#include "assemNode.h"
#include "ast.h"
#include <iostream>

std::unique_ptr<AsmPrg> convertProg(const ASTNode *astNode);
void codegen(const AsmPrg *program, std::ostream &output);
#endif