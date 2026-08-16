#ifndef CODEGEN_H
#define CODEGEN_H
#include <iostream>
#include "assemNode.h"
#include "ast.h"

std::unique_ptr<AsmPrg> convertProg(const ASTNode* astNode);
void codegen(const AsmPrg* program, std::ostream& output);
#endif