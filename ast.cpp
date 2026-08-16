#include "ast.h"

void FuncNode::ChildrenPrint() const {
    for (const auto& stm : statements) {
        stm->Print();
    }
}

void ReturnStm::ChildrenPrint() const {
    if (exp) {
        exp->Print();
    }
}