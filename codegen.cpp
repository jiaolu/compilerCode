
#include "codegen.h"


std::unique_ptr<AsmOperand> convertExp(const ASTNode* astNode) {
    if (auto constExp = dynamic_cast<const ConstantExp*>(astNode)) {
        unsigned value = std::stoul(constExp->value);
        return std::make_unique<AsmImmediate>(value);
    }
    return nullptr;
}

void convertInstruction(const ASTNode* astNode, std::vector<std::unique_ptr<AsmInst>>& instructions) {
    if (auto returnStm = dynamic_cast<const ReturnStm*>(astNode)) {
        auto exp = convertExp(returnStm->exp.get());
        if (exp) {
            instructions.push_back(std::make_unique<AsmMov>(std::move(exp), std::make_unique<AsmRegister>()));
        }
        instructions.push_back(std::make_unique<AsmRet>());
    }
}

std::unique_ptr<AsmFunc> convertFunc(const ASTNode* astNode) {
    std::unique_ptr<AsmFunc> asmFunc = nullptr;
    if (auto funcNode = dynamic_cast<const FuncNode*>(astNode)) {
        asmFunc = std::make_unique<AsmFunc>(funcNode->funcName);
        for (const auto& statement : funcNode->statements) {
            convertInstruction(statement.get(), asmFunc->instructions);
        }
    }
    return asmFunc;
}

std::unique_ptr<AsmPrg> convertProg(const ASTNode* astNode) {
    auto asmProgram = std::make_unique<AsmPrg>();
    if (auto progNode = dynamic_cast<const ProgNode*>(astNode)) {
           const ASTNode* funcNode = progNode->children[0].get();
            asmProgram->func = convertFunc(funcNode);

    }
        return asmProgram;
}



void codegen(const AsmPrg* program, std::ostream& output) {
    program->output(output);
        // Placeholder for actual code generation logic
        // This function should traverse the AsmPrg structure and generate assembly code
}
